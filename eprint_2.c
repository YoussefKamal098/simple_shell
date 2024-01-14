#include "shell.h"

/**
 * print_open_file_err_msg - print open file error message to standard error
 * @file_name: file name
 * @info: info of program
 */

void print_open_file_err_msg(program_info_t *info, char *file_name)
{
	_eputs(info->name);
	_eputs(": 0: Can't open ");
	_eputs(file_name);
	_eputs("\n");
}

/**
 *  print_illegal_number_err_msg -  print illegal number message to
 * standard error
 * @info: program information
 */

void print_illegal_number_err_msg(program_info_t *info)
{
	char *num = get_list_node_value_at_index(info->curr_cmd_tokens, 1);

	print_prefix_err_msg(info);
	_eputs(info->curr_cmd_name);
	_eputs(": Illegal number: ");
	_eputs(num);
	_eputs("\n");
}

/**
 * print_syntax_err_msg -  print syntax error message to
 * standard error
 * @info: program information
 * @err: syntax error
 */

void print_syntax_err_msg(program_info_t *info, char *err)
{
	print_prefix_err_msg(info);
	_eputs("Syntax error: ");
	_eputs(err);
	_eputs(" unexpected\n");
}

/**
 * print_unsupported_feature_err_msg -  print unsupported feature error
 * message to standard error
 * @info: program information
 * @feature: unix shell feature that my shell doesn't support
 */

void print_unsupported_feature_err_msg(program_info_t *info, char *feature)
{
	print_prefix_err_msg(info);
	_eputs("This shell doesn't support ");
	_eputs(feature);
	_eputs(" feature\n");
}

/**
 * print_no_such_file_or_dir_err_msg - print no such file or directory
 * error message to standard error
 * @info: program information
 */
void print_no_such_file_or_dir_err_msg(program_info_t *info)
{
	char *second_token = get_list_node_value_at_index(info->curr_cmd_tokens, 1);

	_eputs(info->curr_cmd_name);
	_eputs(": ");
	_eputs(second_token);
	_eputs(": No such file or directory\n");
}
