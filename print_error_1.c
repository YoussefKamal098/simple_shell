#include "shell.h"

/**
 * _puts_error - print error message to standard error
 * @str: string
 * Return: number of written bytes or -1 if fails to write
 */

int _puts_error(char *str)
{
	int bytes = write(STDERR_FILENO, str, _strlen(str));

	if (bytes == -1)
		perror("Error writing to the file");

	return (bytes);
}

/**
 * print_error_msg - print error message to standard error
 * @info: program information
 * @error_code: error code
 */
void print_error_msg(program_info_t *info, int error_code)
{
	if (error_code == ILLEGAL_NUMBER)
		print_illegal_number_msg(info);
	else if (error_code == COMMAND_NOT_FOUND)
		print_msg(info, ": not found");
	else if (error_code == PERMISSION_DENIED)
		print_msg(info, ": Permission denied");
	else if (error_code == NO_SUCH_FILE_OR_DIRECTORY)
		print_no_such_file_or_directory_error_msg(info);
}

/**
 * print_msg - print error message to
 * standard error
 * @info: program information
 * @msg: error message
 */

void print_msg(program_info_t *info, char *msg)
{
	print_prefix_err_msg(info);
	_puts_error(info->curr_cmd_name);
	_puts_error(msg);
	_puts_error("\n");
}

/**
 * print_prefix_err_msg - print prefix error message to
 * standard error
 * @info: program information
 */

void print_prefix_err_msg(program_info_t *info)
{
	char *command_exec_num = _itoa(info->exec_counter, 1);

	_puts_error(info->name);
	_puts_error(": ");
	_puts_error(command_exec_num);
	_puts_error(": ");

	free(command_exec_num);
}
