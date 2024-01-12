#include "shell.h"

int is_path(program_info_t *info);
int is_exist(int code);

/**
 * find_program - find executable program
 * @info: program information
 * Return: 0 if success, error code otherwise
 */

int find_program(program_info_t *info)
{
	int i, code = 0;
	char **directories;
	char *file_path;

	if (is_path(info))
		return (check_file(info->curr_cmd_name));

	directories = tokenize_env_path(info);
	if (!directories || !directories[0])
	{
		errno = COMMAND_NOT_FOUND;
		return (errno);
	}

	for (i = 0; directories[i]; i++)
	{
		file_path = str_concat(directories[i], info->curr_cmd_name);
		code = check_file(file_path);

		if (is_exist(code))
		{
			errno = 0;
			update_list_node_str_at_index(info->curr_cmd_tokens, file_path, 0);
			free_array_of_pointers(directories), free(file_path);
			return (code);
		}

		free(file_path);
	}

	free_list(&info->curr_cmd_tokens);
	free_array_of_pointers(directories);
	return (code);
}

/**
 * is_path - check if it is a path
 * @info: program information
 * Return: 1 if condition true 0 otherwise
 */

int is_path(program_info_t *info)
{
	return (info->curr_cmd_name[0] == '/' || info->curr_cmd_name[0] == '.');
}

/**
 * is_exist - check if the return code of check_file function
 *  means that file or directory exist
 * @code: error code
 * Return: 1 if condition true 0 otherwise
 */

int is_exist(int code)
{
	return (code == 0 || code == PERMISSION_DENIED);
}
