#include "shell.h"

void print_alias_key(dict_t *alias, char *key);

/**
 * builtin_alias_cmd - add, remove, show alias
 * @info: program information
 * Return: 0 if success or error code if failed
 */
int builtin_alias_cmd(program_info_t *info)
{
	int i, j;
	char **tokens = list_to_strs(info->curr_cmd_tokens), *key, *value, *temp;

	if (!tokens[1])
		print_dict(info->alias, "=", "'");

	for (i = 1; tokens[i]; i++)
	{
		j = get_delimiter_index(tokens[i], "=");
		if (j != -1)
		{
			tokens[i][j] = '\0';
			key = &tokens[i][0];
			value = &tokens[i][j + 1];
			temp = get_dict_key(info->alias, value);
			value = temp ? temp : value;
			set_dict_key(&info->alias, key, value ? value : "");
		}
		else
			print_alias_key(info->alias, tokens[i]);
	}

	free_pointers_arr(tokens);
	return (0);
}

/**
 * print_alias_key - print alias variable
 * @alias: aliases
 * @key: key of alias
 */

void print_alias_key(dict_t *alias, char *key)
{
	char *value = get_dict_key(alias, key);

	if (!value)
		return;

	_puts(key);
	_puts("=");
	_puts("'");
	_puts(value);
	_puts("'\n");
}
