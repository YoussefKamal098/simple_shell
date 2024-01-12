#include "shell.h"

/*
 *handle multiple statements like:
 *env key=value key key=value
 *env key=value key key
 *env key key key=value
 */

/**
 * builtin_env_command - print environment variables
 * @info: program information
 * Return: 0 if success or error code if failed
 */
int builtin_env_command(program_info_t *info)
{
	size_t i;
	char key[BUFFER_SIZE] = {'\0'}, *value;
	char *env_second_token = get_node_str_at_index(info->curr_cmd_tokens, 1);

	if (!env_second_token)
	{
		print_env(info);
		return (0);
	}

	for (i = 0; env_second_token[i]; i++)
	{
		if (env_second_token[i] == '=')
		{
			value = get_env_key(info, key);
			if (value)
				set_env_key(info, key, &env_second_token[i + 1]);

			print_env(info);
			if (value)
				set_env_key(info, key, value), free(value);
			else
				_puts(env_second_token), _puts("\n");

			return (0);
		}

		key[i] = env_second_token[i];
	}

	errno = COMMAND_NOT_FOUND;
	return (NO_SUCH_FILE_OR_DIRECTORY);
}

/**
 * builtin_set_env - initialize a new environment variable,
 * or modify an existing one
 * @info: program information
 * Return: 0 if success or error code if failed
 */
int builtin_set_env(program_info_t *info)
{
	char *key = get_node_str_at_index(info->curr_cmd_tokens, 1);
	char *value = get_node_str_at_index(info->curr_cmd_tokens, 2);
	char *third_token = get_node_str_at_index(info->curr_cmd_tokens, 3);

	if (!key || !value)
		return (0);

	if (third_token)
	{
		errno = E2BIG, perror(info->curr_cmd_name);
		return (errno);
	}

	set_env_key(info, key, value);
	return (0);
}

/**
 * builtin_unset_env - remove an environment variable
 * @info: program information
 * Return: 0 if success or error code if failed
 */
int builtin_unset_env(program_info_t *info)
{
	char *key = get_node_str_at_index(info->curr_cmd_tokens, 1);
	char *second_token = get_node_str_at_index(info->curr_cmd_tokens, 2);

	if (!key)
		return (0);

	if (second_token)
	{
		errno = E2BIG, perror(info->curr_cmd_name);
		return (errno);
	}

	unset_env_key(info, key);
	return (0);
}
