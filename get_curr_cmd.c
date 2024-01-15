#include "shell.h"

int can_read_new_input(program_info_t *info);

/**
 * get_curr_cmd - get current command to execute
 * @info: program information
 * Return: length of current command or -1 if it reach end of the file or
 * read operation failed
 */
int get_curr_cmd(program_info_t *info)
{
	int read_bytes;
	char buffer[BUFF_SIZE] = {'\0'};

	if (can_read_new_input(info))
	{
		read_bytes = _getline(info->fd, buffer, BUFF_SIZE - 1);

		if (read_bytes == -1)
			return (EOF);
		if (read_bytes == 0)
			return (EOF);
		if (validate_input_line(info, buffer))
			return (0);

		free_list(&info->next_cmds);
		free_list(&info->next_operators);
		tokenize_input_line(info, buffer);
	}
	else
	{
		if (info->next_operators)
			free(shift_list(&info->next_operators));
	}

	if (!info->next_cmds)
		return (0);

	info->curr_cmd = shift_list(&info->next_cmds);
	return (_strlen(info->curr_cmd));
}

/**
 * can_read_new_input - check if can read new input
 * @info: program information
 * Return: 1 if condition true or 0 otherwise
 */

int can_read_new_input(program_info_t *info)
{
	return ((!info->next_cmds ||
		 (info->next_operators &&
		  _strcmp(info->next_operators->val, "&&") == 0 && errno != 0) ||
		 (info->next_operators &&
		  _strcmp(info->next_operators->val, "||") == 0 && errno == 0)));
}

/**
 * is_and_operator - check if it is && operator
 * @input_line:  input line that will by checked
 * @i: index of input line
 * Return: 1 if condition true 0 or otherwise
 */

int is_and_operator(char *input_line, int i)
{
	return (input_line[i] == '&' && input_line[i + 1] == '&');
}

/**
 * is_or_operator - check if is ||  operator
 * @input_line:  input line that will by checked
 * @i: index of input line
 * Return: 1 if condition true or 0 otherwise
 */

int is_or_operator(char *input_line, int i)
{
	return (input_line[i] == '|' && input_line[i + 1] == '|');
}

/**
 * is_double_semicolon - check if is ";;" operator
 * @input_line: input line that will by checked
 * @i: index of input line
 * Return: 1 if condition true or 0 otherwise
 */

int is_double_semicolon(char *input_line, int i)
{
	return (input_line[i] == ';' && input_line[i + 1] == ';');
}
