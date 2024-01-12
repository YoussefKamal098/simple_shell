#include "shell.h"

int set_working_directory(program_info_t *info, char *new_dir);
int set_pre_working_directory(program_info_t *info);

/**
 * builtin_cd_command - change current working directory
 * @info: program information
 * Return: 0 if success or error code if failed
 */
int builtin_cd_command(program_info_t *info)
{
	char *home_dir = get_env_key(info, "HOME");
	char *second_token = get_node_str_at_index(info->curr_cmd_tokens, 1);
	char old_dir[BUFFER_SIZE] = {'\0'};
	int err_code;

	if (second_token)
	{
		if (!_strcmp(second_token, "-"))
		{
			err_code = set_pre_working_directory(info);
			_puts(get_env_key(info, "PWD"));
			_puts("\n");
			return (err_code);
		}
		else
		{
			return (set_working_directory(info, second_token));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(old_dir, BUFFER_SIZE - 1);

		return (set_working_directory(info, home_dir));
	}

	return (0);
}

/**
 * set_working_directory - set the current working directory to
 * new directory
 * @info: program information
 * @new_dir: path to new directory
 * Return: 0 if success or error code if failed
 */
int set_working_directory(program_info_t *info, char *new_dir)
{
	char old_dir[BUFFER_SIZE] = {'\0'};
	int err_code = 0;

	getcwd(old_dir, BUFFER_SIZE - 1);

	err_code = chdir(new_dir);
	if (err_code == -1)
	{
		errno = 2;
		return (CANNOT_CD_TO);
	}

	set_env_key(info, "PWD", new_dir);
	set_env_key(info, "OLDPWD", old_dir);
	return (0);
}
/**
 * set_pre_working_directory - set the current working directory to
 * previous directory
 * @info: program information
 * Return: 0 if success or error code if failed
 */
int set_pre_working_directory(program_info_t *info)
{
	char *old_dir;
	int err_code = 0;

	old_dir = get_env_key(info, "OLDPWD");
	if (old_dir)
		err_code = set_working_directory(info, old_dir);

	return (err_code);
}
