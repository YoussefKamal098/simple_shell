#include "shell.h"

/**
 * print_open_file_error_msg - print open file error message to standard error
 * @file_name: file name
 * @info: info of program
 */

void print_open_file_error_msg(program_info_t *info, char *file_name)
{
	_puts_error(info->name);
	_puts_error(": 0: Can't open ");
	_puts_error(file_name);
	_puts_error("\n");
}

/**
 *  print_illegal_number_msg -  print illegal number message to
 * standard error
 * @info: program information
 */

void print_illegal_number_msg(program_info_t *info)
{
	char *num = get_list_node_str_at_index(info->curr_cmd_tokens, 1);

	print_prefix_err_msg(info);
	_puts_error(info->curr_cmd_name);
	_puts_error(": Illegal number: ");
	_puts_error(num);
	_puts_error("\n");
}

/**
 * print_syntax_error_msg -  print syntax error message to
 * standard error
 * @info: program information
 * @error: syntax error
 */

void print_syntax_error_msg(program_info_t *info, char *error)
{
	print_prefix_err_msg(info);
	_puts_error("Syntax error: ");
	_puts_error(error);
	_puts_error(" unexpected\n");
}

/**
 * print_unsupported_feature_error_msg -  print unsupported feature error
 * message to standard error
 * @info: program information
 * @feature: unix shell feature that my shell doesn't support
 */

void print_unsupported_feature_error_msg(program_info_t *info, char *feature)
{
	print_prefix_err_msg(info);
	_puts_error("This shell doesn't support ");
	_puts_error(feature);
	_puts_error(" feature\n");
}

/**
 * print_no_such_file_or_directory_error_msg - print no such file or directory
 * message to standard error
 * @info: program information
 */
void print_no_such_file_or_directory_error_msg(program_info_t *info)
{
	char *second_token = get_list_node_str_at_index(info->curr_cmd_tokens, 1);

	_puts_error(info->curr_cmd_name);
	_puts_error(": ");
	_puts_error(second_token);
	_puts_error(": No such file or directory\n");
}
