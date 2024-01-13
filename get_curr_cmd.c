#include "shell.h"

int can_read_new_input(program_info_t *info);

/**
 * get_curr_cmd - get current cmd to execute
 * @info: program information
 * Return: read bytes or -1 if it reach end of the file
 */
int get_curr_cmd(program_info_t *info)
{
	int read_bytes;
	char buffer[BUFFER_SIZE] = {'\0'}, *cmd, *ops;

	if (can_read_new_input(info))
	{
		read_bytes = _getline(info->fd, buffer, BUFFER_SIZE - 1);

		if (read_bytes == -1)
			return (EOF);
		if (read_bytes == 0)
			return (EOF);
		if (validate_buffer(info, buffer))
			return (0);

		free_list(&info->next_cmds);
		free_list(&info->next_operators);
		tokenize_buffer(info, buffer);
	}
	else
	{
		if (info->next_operators)
		{
			ops = shift_list(&info->next_operators);
			if (ops)
				free(ops);
		}
	}

	if (!info->next_cmds)
		return (0);

	cmd = shift_list(&info->next_cmds);
	info->curr_cmd = _strdup(cmd), free(cmd);
	return (_strlen(info->curr_cmd));
}

/**
 * can_read_new_input - check if can read new input
 * @info: program information
 * Return: 1 if condition true 0 otherwise
 */

int can_read_new_input(program_info_t *info)
{
	return ((!info->next_cmds ||
		 (info->next_operators &&
		  _strcmp(info->next_operators->value, "&&") == 0 && errno != 0) ||
		 (info->next_operators &&
		  _strcmp(info->next_operators->value, "||") == 0 && errno == 0)));
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
 * is_double_semicolon - check if is or double_semicolon operator
 * @buffer: buffer that will by checked
 * @i: index of buffer
 * Return: 1 if condition true 0 otherwise
 */

int is_double_semicolon(char *buffer, int i)
{
	return (buffer[i] == ';' && buffer[i + 1] == ';');
}
