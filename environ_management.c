#include "shell.h"

int update_env_node_at_index(list_t *env, char *key, char *value, size_t idx);
int env_key_search(list_t *env, char *key);

/**
 * get_env_key - gets the value of the environment variable
 * @key: the environment variable
 * @info: program information
 * Return: a pointer to the duplicated value of the variable
 * or NULL if it doesn't exist
 */
char *get_env_key(program_info_t *info, char *key)
{
	int i;

	if (!key)
		return (NULL);

	i = env_key_search(info->env, key);

	if (i != -1)
		return (get_node_str_at_index(info->env, i) + _strlen(key) + 1);

	return (NULL);
}

/**
 * set_env_key - overwrite the value of the environment variable
 * or create it if doesn't exist.
 * @key: the environment variable
 * @value: value to assigned to environment variable key
 * @info: program information
 * Return: -1 if any of the parameters are NULL, 0 if success.
 */
int set_env_key(program_info_t *info, char *key, char *value)
{
	int i;
	char *temp;

	if (!key || !value)
		return (-1);

	i = env_key_search(info->env, key);

	if (i != -1)
	{
		update_env_node_at_index(info->env, key, value, i);
		return (0);
	}

	temp = str_n_concat(3, key, "=", value);
	list_push(&info->env, temp), free(temp);
	return (0);
}

/**
 * unset_env_key - remove a key from the environment
 * @key: the environment variable
 * @info: program information
 * Return: 0 if the key was removed, -1 if the key does not exist
 */
int unset_env_key(program_info_t *info, char *key)
{
	int i = 0;

	if (!key)
		return (-1);

	i = env_key_search(info->env, key);

	if (i != -1)
	{
		remove_node_at_index(&info->env, i);
		return (0);
	}

	return (-1);
}

/**
 * update_env_node_at_index - update environment variable
 * with value at index
 * @env: list of environment variable
 * @key: the environment variable
 * @value: value to assigned to environment variable key
 * @idx: index of environment variable to by changed
 * Return: 0
 */
int update_env_node_at_index(list_t *env, char *key, char *value, size_t idx)
{
	char *temp = str_n_concat(3, key, "=", value);

	update_node_str_at_index(env, temp, idx), free(temp);
	return (0);
}

/**
 *  env_key_search -  env_key_search
 * with value at index
 * @env: list of environment variable
 * @key: the environment variable
 * Return: index of env node with key or -1 if not found
 */

int env_key_search(list_t *env, char *key)
{
	int i;
	char *temp;

	temp = str_concat(key, "=");
	i = list_search(env, temp);
	free(temp);

	return (i);
}

/**
 * print_env - print environment variables
 * @info: program information
 */
void print_env(program_info_t *info)
{
	errno = 0;
	print_list_str(info->env, "\n");
}
