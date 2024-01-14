#include "shell.h"

/**
 * _eputs - print string to standard error
 * @str: string
 * Return: number of written bytes or -1 if it failed to write
 */

int _eputs(char *str)
{
	int bytes = write(STDERR_FILENO, str, _strlen(str));

	if (bytes == -1)
		perror("Error");

	return (bytes);
}

/**
 * print_stderr_msg - print message to standard error
 * @info: program information
 * @err_code: error code
 */
void print_stderr_msg(program_info_t *info, int err_code)
{
	if (err_code == ILLEGAL_NUMBER)
		print_illegal_number_err_msg(info);
	else if (err_code == CANNOT_CD_TO)
		print_cannot_cd_to_err_msg(info);
	else if (err_code == CMD_NOT_FOUND)
		print_err_msg(info, ": not found");
	else if (err_code == PERMISSION_DENIED)
		print_err_msg(info, ": Permission denied");
	else if (err_code == NO_SUCH_FILE_OR_DIR)
		print_no_such_file_or_dir_err_msg(info);
}

/**
 * print_err_msg - print error message to
 * standard error
 * @info: program information
 * @msg: error message
 */

void print_err_msg(program_info_t *info, char *msg)
{
	print_prefix_err_msg(info);
	_eputs(info->curr_cmd_name);
	_eputs(msg);
	_eputs("\n");
}

/**
 * print_prefix_err_msg - print prefix error message to
 * standard error
 * @info: program information
 */

void print_prefix_err_msg(program_info_t *info)
{
	char *command_exec_num = _itoa(info->exec_counter, 1);

	_eputs(info->name);
	_eputs(": ");
	_eputs(command_exec_num);
	_eputs(": ");

	free(command_exec_num);
}

/**
 * print_cannot_cd_to_err_msg - print can't cd to error message to
 * standard error
 * @info: program information
 */

void print_cannot_cd_to_err_msg(program_info_t *info)
{
	char *dir = get_list_node_value_at_index(info->curr_cmd_tokens, 1);

	print_prefix_err_msg(info);
	_eputs(info->curr_cmd_name);
	_eputs(": can't cd to ");
	_eputs(dir);
	_eputs("\n");
}
