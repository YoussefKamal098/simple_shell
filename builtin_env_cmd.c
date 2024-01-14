#include "shell.h"

void print_env(dict_t *env);

/**
 * builtin_env_cmd - print environment variables
 * @info: program information
 * Return: 0 if success or error code if failed
 */
int builtin_env_cmd(program_info_t *info)
{
	char *value, *second_token, key[BUFF_SIZE] = {'\0'};
	size_t i;

	second_token = get_list_node_value_at_index(info->curr_cmd_tokens, 1);
	if (!second_token)
	{
		print_env(info->env);
		return (0);
	}

	for (i = 0; second_token[i]; i++)
	{
		if (second_token[i] == '=')
		{
			value = _strdup(get_dict_key(info->env, key));
			if (value)
				set_dict_key(&info->env, key, &second_token[i + 1]);

			print_env(info->env);
			if (value)
				set_dict_key(&info->env, key, value), free(value);
			else
				_puts(second_token), _puts("\n");

			return (0);
		}

		key[i] = second_token[i];
	}

	errno = CMD_NOT_FOUND;
	return (NO_SUCH_FILE_OR_DIR);
}

/**
 * builtin_setenv_cmd - initialize a new environment variable,
 * or modify an existing one
 * @info: program information
 * Return: 0 if success or error code if failed
 */
int builtin_setenv_cmd(program_info_t *info)
{
	char *key = get_list_node_value_at_index(info->curr_cmd_tokens, 1);
	char *value = get_list_node_value_at_index(info->curr_cmd_tokens, 2);
	char *third_token = get_list_node_value_at_index(info->curr_cmd_tokens, 3);

	if (!key || !value)
		return (0);
	if (third_token)
	{
		errno = E2BIG, perror(info->curr_cmd_name);
		return (errno);
	}

	set_dict_key(&info->env, key, value);
	return (0);
}

/**
 * builtin_unsetenv_cmd - remove an environment variable
 * @info: program information
 * Return: 0 if success or error code if failed
 */
int builtin_unsetenv_cmd(program_info_t *info)
{
	char *key = get_list_node_value_at_index(info->curr_cmd_tokens, 1);
	char *second_token = get_list_node_value_at_index(info->curr_cmd_tokens, 2);

	if (!key)
		return (0);
	if (second_token)
	{
		errno = E2BIG, perror(info->curr_cmd_name);
		return (errno);
	}

	unset_dict_key(&info->env, key);
	return (0);
}

/**
 * print_env - print environment variables
 * @env: head of environment variables list
 */
void print_env(dict_t *env)
{
	errno = 0;
	print_dict(env, "=", "");
}
