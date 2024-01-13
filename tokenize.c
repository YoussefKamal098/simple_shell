#include "shell.h"

/**
 * tokenize_curr_cmd - separate the string with delimiters
 * @info: program information
 */

void tokenize_curr_cmd(program_info_t *info)
{
	char *delimiters = " \t";
	char *curr_cmd, *token;

	curr_cmd = _strdup(info->curr_cmd);

	token = _strtok(curr_cmd, delimiters);
	if (!token)
	{
		free(curr_cmd);
		return;
	}

	list_push(&info->curr_cmd_tokens, token);
	info->curr_cmd_name = _strdup(token);

	while (token)
	{
		token = _strtok(NULL, delimiters);
		if (token)
			list_push(&info->curr_cmd_tokens, token);
	}

	/**
	 * handle quote and double quote nested quote and double quote and
	 * double braces and calcs
	 * cases like these:
	 * echo $((ls))
	 * echo $((1+6))
	 * 1- echo "        $?    ",
	 * 2- ls " || ",
	 * 3- echo "word "word word " "   word "word"  " " word word 'word word' " ",
	 */

	free(curr_cmd);
}

/**
 * tokenize_env_path - separate the PATH environment variable with
 * ':' character
 * @info: program info
 * Return: pointer of directories (strings)
 */

char **tokenize_env_path(program_info_t *info)
{
	size_t i, dirs_counter = 0;
	char **tokens, *token, *path, *delimiter = ":";

	path = _strdup(get_dict_key(info->env, "PATH"));

	if (!path || path[0] == '\0')
		return (NULL);

	for (i = 0; path[i]; i++)
		if (path[i] == *delimiter)
			dirs_counter++;

	tokens = (char **)malloc(sizeof(char *) * (dirs_counter + 2));
	if (!tokens)
	{
		errno = ENOMEM, perror("Error");
		return (NULL);
	}

	i = 0, token = tokens[i] = _strdup(_strtok(path, delimiter));
	while (token)
	{
		i++, token = _strtok(NULL, delimiter);
		if (token)
			tokens[i] = strconcat(token, "/");
	}

	tokens[i] = NULL, free(path);
	return (tokens);
}

/**
 * tokenize_buffer - separate the buffer with delimiters
 * (|| && '\n' ;) to set of commands
 * @buffer: buffer of getline function
 * @next_cmds: list that store the future commands
 * @next_ops: list that store the future operators
 */
void tokenize_buffer(char *buffer, list_t **next_cmds, list_t **next_ops)
{
	size_t i, j = 0;
	char cmd[BUFFER_SIZE];

	for (i = 0; buffer[i]; i++)
	{
		if (is_and_operator(buffer, i) || is_or_operator(buffer, i))
		{
			cmd[j] = '\0';
			list_push(next_cmds, cmd);
			list_push(next_ops, buffer[i] == '&' ? "&&" : "||");

			i++, j = 0;
		}
		else if (buffer[i] == ';' || buffer[i] == '\n')
		{
			cmd[j] = '\0';
			if (cmd[0] != '\0')
				list_push(next_cmds, cmd);
			if (buffer[i] == ';')
				list_push(next_ops, ";");
			j = 0;
		}
		else
			cmd[j] = buffer[i], j++;
	}

	if (j != 0)
		cmd[j] = '\0', list_push(next_cmds, cmd);
}
