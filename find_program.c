#include "shell.h"

int is_path(program_info_t *info);
int is_exist(int code);

/**
 * find_program - find executable program
 * @info: program information
 * Return: 0 if success or error code otherwise
 */

int find_program(program_info_t *info)
{
	int i, code = 0;
	char **dirs;
	char *file_path;

	if (is_path(info))
		return (check_file(info->curr_cmd_name));

	dirs = tokenize_env_path(info);
	if (!dirs || !dirs[0])
	{
		errno = CMD_NOT_FOUND;
		return (errno);
	}

	for (i = 0; dirs[i]; i++)
	{
		file_path = strconcat(dirs[i], info->curr_cmd_name);
		code = check_file(file_path);

		if (is_exist(code))
		{
			errno = 0;
			update_list_node_value_at_index(info->curr_cmd_tokens, file_path, 0);
			free_pointers_arr(dirs), free(file_path);
			return (code);
		}

		free(file_path);
	}

	free_list(&info->curr_cmd_tokens);
	free_pointers_arr(dirs);
	return (code);
}

/**
 * is_path - check if it is a path
 * @info: program information
 * Return: 1 if condition true or 0 otherwise
 */

int is_path(program_info_t *info)
{
	return (info->curr_cmd_name[0] == '/' || info->curr_cmd_name[0] == '.');
}

/**
 * is_exist - check if the return code of check_file function
 *  means that file or directory exist
 * @code: error code
 * Return: 1 if condition true pr 0 otherwise
 */

int is_exist(int code)
{
	return (code == 0 || code == PERMISSION_DENIED);
}
