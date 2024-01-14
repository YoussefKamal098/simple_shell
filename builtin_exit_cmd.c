#include "shell.h"

/**
 * builtin_exit_cmd - command that exit from shell with status code
 * @info: program information
 * Return: 0 if success or error code if failed
 */

int builtin_exit_cmd(program_info_t *info)
{
	char *second_token = get_list_node_value_at_index(info->curr_cmd_tokens, 1);

	if (second_token)
	{
		if (is_pos_int(second_token))
			errno = _atoi(second_token);
		else
		{
			errno = ENOENT;
			return (ILLEGAL_NUMBER);
		}
	}

	free_all_program_info(info);
	exit(errno);
}
