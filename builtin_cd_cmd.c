#include "shell.h"

int set_working_dir(program_info_t *info, char *new_dir);
int set_pre_working_dir(program_info_t *info);

/**
 * builtin_cd_cmd - change current working directory
 * @info: program information
 * Return: 0 if success or error code if failed
 */
int builtin_cd_cmd(program_info_t *info)
{
	char *home_dir = get_dict_key(info->env, "HOME");
	char *second_token = get_list_node_value_at_index(info->curr_cmd_tokens, 1);
	char old_dir[BUFFER_SIZE] = {'\0'};
	int code;

	if (second_token)
	{
		if (!_strcmp(second_token, "-"))
		{
			code = set_pre_working_dir(info);
			_puts(get_dict_key(info->env, "PWD"));
			_puts("\n");
			return (code);
		}
		else
		{
			return (set_working_dir(info, second_token));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(old_dir, BUFFER_SIZE - 1);

		return (set_working_dir(info, home_dir));
	}

	return (0);
}

/**
 * set_working_dir - set the current working directory to
 * new directory
 * @info: program information
 * @new_dir: path to new directory
 * Return: 0 if success or error code if failed
 */
int set_working_dir(program_info_t *info, char *new_dir)
{
	char old_dir[BUFFER_SIZE] = {'\0'};
	int code = 0;

	getcwd(old_dir, BUFFER_SIZE - 1);

	code = chdir(new_dir);
	if (code == -1)
	{
		errno = 2;
		return (CANNOT_CD_TO);
	}

	set_dict_key(&info->env, "PWD", new_dir);
	set_dict_key(&info->env, "OLDPWD", old_dir);
	return (0);
}
/**
 * set_pre_working_dir - set the current working directory to
 * previous directory
 * @info: program information
 * Return: 0 if success or error code if failed
 */
int set_pre_working_dir(program_info_t *info)
{
	char *old_dir;
	int code = 0;

	old_dir = get_dict_key(info->env, "OLDPWD");
	if (old_dir)
		code = set_working_dir(info, old_dir);

	return (code);
}
