#include "shell.h"

int can_read_new_input(list_t *next_cmds, list_t *next_ops);

/*
 * handle invalid quotes and double quotes and braces
 * like this cases: echo " , echo ' , echo " ' , echo ' ", echo (, echo (()
 */

/*
 * handle to read one line only in getline function
 * handle case that user input characters larger than buffer size
 */

/**
 * _getline - read line from the file_descriptor
 * @info: program information
 * Return: read bytes or -1 if it reach end of the file
 */
int _getline(program_info_t *info)
{
	int read_bytes;
	char buffer[BUFFER_SIZE] = {'\0'}, *cmd, *ops;
	static list_t *next_commands, *next_operators;

	if (can_read_new_input(next_commands, next_operators))
	{
		read_bytes = read(info->file_descriptor, &buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			perror("Error reading from the file");
			return (EOF);
		}
		if (read_bytes == 0)
			return (EOF);
		if (check_for_syntax_error(info, buffer))
			return (0);
		if (check_for_unsupported_features(info, buffer))
			return (0);

		free_list(&next_commands), free_list(&next_operators);
		tokenize_buffer(buffer, &next_commands, &next_operators);
	}
	else
	{
		if (next_operators)
		{
			ops = shift_list(&next_operators);
			if (ops)
				free(ops);
		}
	}

	if (!next_commands)
		return (0);

	cmd = shift_list(&next_commands);
	info->curr_cmd = _strdup(cmd), free(cmd);
	return (_strlen(info->curr_cmd));
}

/**
 * can_read_new_input - check if can read new input
 * @next_cmds: list that store the future commands
 * @next_ops: list that store the future operators
 * Return: 1 if condition true 0 otherwise
 */

int can_read_new_input(list_t *next_cmds, list_t *next_ops)
{
	return ((!next_cmds ||
		 (next_ops && _strcmp(next_ops->str, "&&") == 0 && errno != 0) ||
		 (next_ops && _strcmp(next_ops->str, "||") == 0 && errno == 0)));
}

/**
 * is_and_operator - check if is and operator  operator
 * @buffer:  buffer that will by checked
 * @i: index of buffer
 * Return: 1 if condition true 0 otherwise
 */

int is_and_operator(char *buffer, int i)
{
	return (buffer[i] == '&' && buffer[i + 1] == '&');
}

/**
 * is_or_operator - check if is or operator  operator
 * @buffer:  buffer that will by checked
 * @i: index of buffer
 * Return: 1 if condition true 0 otherwise
 */

int is_or_operator(char *buffer, int i)
{
	return (buffer[i] == '|' && buffer[i + 1] == '|');
}

/**
 * is_double_semicolon_operator - check if is or double_semicolon operator
 * @buffer: buffer that will by checked
 * @i: index of buffer
 * Return: 1 if condition true 0 otherwise
 */

int is_double_semicolon_operator(char *buffer, int i)
{
	return (buffer[i] == ';' && buffer[i + 1] == ';');
}
