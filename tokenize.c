#include "shell.h"

/**
 * tokenize_curr_cmd - tokenize current command with ' ', \t delimiters
 * @info: program information
 */

void tokenize_curr_cmd(program_info_t *info)
{
	char *delims = " \t";
	char *curr_cmd, *token;

	curr_cmd = _strdup(info->curr_cmd);
	token = _strtok(curr_cmd, delims);
	if (!token)
	{
		free(curr_cmd);
		return;
	}

	list_push(&info->curr_cmd_tokens, token);
	info->curr_cmd_name = _strdup(token);

	while (token)
	{
		token = _strtok(NULL, delims);
		if (token)
			list_push(&info->curr_cmd_tokens, token);
	}

	free(curr_cmd);
}

/**
 * tokenize_env_path - tokenize current PATH environment variable with
 * ':' delimiters
 * @info: program information
 * Return: array of strings (directories)
 */

char **tokenize_env_path(program_info_t *info)
{
	size_t i, dirs_counter = 0;
	char **tokens, *token, *path, *delims = ":";

	path = _strdup(get_dict_key(info->env, "PATH"));

	if (!path)
		return (NULL);
	if (*path == '\0')
	{
		free(path);
		return (NULL);
	}

	for (i = 0; path[i]; i++)
		if (path[i] == *delims)
			dirs_counter++;

	tokens = (char **)malloc(sizeof(char *) * (dirs_counter + 2));
	if (!tokens)
	{
		errno = ENOMEM, perror("Error");
		return (NULL);
	}

	i = 0;
	token = _strtok(path, delims);
	while (token)
	{
		tokens[i] = strconcat(token, "/");
		i++, token = _strtok(NULL, delims);
	}

	tokens[i] = NULL, free(path);
	return (tokens);
}

/**
 * tokenize_input_line - tokenize input line with  (|| && '\n' ;) delimiters
 * @info: program information
 * @input_line: input line
 */
void tokenize_input_line(program_info_t *info, char *input_line)
{
	size_t i, j = 0;
	char cmd[BUFF_SIZE];

	for (i = 0; input_line[i]; i++)
	{
		if (is_and_operator(input_line, i) || is_or_operator(input_line, i))
		{
			cmd[j] = '\0';
			list_push(&info->next_cmds, cmd);
			list_push(&info->next_operators, input_line[i] == '&' ? "&&" : "||");
			i++, j = 0;
		}
		else if (input_line[i] == ';' || input_line[i] == '\n')
		{
			cmd[j] = '\0';
			if (cmd[0] != '\0')
				list_push(&info->next_cmds, cmd);
			if (input_line[i] == ';')
				list_push(&info->next_operators, ";");
			j = 0;
		}
		else
			cmd[j] = input_line[i], j++;
	}

	if (j != 0)
		cmd[j] = '\0', list_push(&info->next_cmds, cmd);
}
