#include "shell.h"

int is_single_dollar_sign(char *curr_cmd, size_t i);
int is_errno(char *curr_cmd, size_t i);
int is_proccess_id(char *curr_cmd, size_t i);
int is_comment(char *curr_cmd, size_t i);

/**
 * expand_vars - expand variables
 * @info: program information
 */
void expand_vars(program_info_t *info)
{
	size_t i, j = 0;
	char buffer[BUFF_SIZE] = {'\0'};
	char *curr_cmd = info->curr_cmd, *var, *expansion;
	int idx;

	for (i = 0; curr_cmd[i]; i++)
	{
		if (is_comment(curr_cmd, i))
			break;
		else if (is_errno(curr_cmd, i) || is_proccess_id(curr_cmd, i))
		{
			expansion = _itoa(is_errno(curr_cmd, i) ? errno : getpid(), 1);
			j = add_buffer(buffer, expansion), free(expansion), i++;
		}
		else if (curr_cmd[i] == '$' && !is_single_dollar_sign(curr_cmd, i))
		{
			idx = get_delimiter_index(&curr_cmd[i + 1], "$ ");
			idx = idx == -1 ? _strlen(&curr_cmd[i + 1]) : (size_t)idx;
			var = get_substr_from_to(&curr_cmd[i + 1], 0, idx);
			expansion = get_dict_key(info->env, var), free(var);
			if (expansion)
				j = add_buffer(buffer, expansion);

			i = i + idx;
		}
		else
			buffer[j] = curr_cmd[i], j++;
	}

	if (_strcmp(curr_cmd, buffer))
		free(curr_cmd), info->curr_cmd = _strdup(*buffer ? buffer : "");
}

/**
 * expand_alias - expands aliases
 * @info: program information
 */
void expand_alias(program_info_t *info)
{
	char *val = get_dict_key(info->alias, info->curr_cmd_name);

	if (val)
	{
		free(info->curr_cmd_name);
		info->curr_cmd_name = _strdup(val);
		update_list_node_value_at_index(info->curr_cmd_tokens, val, 0);
	}
}

/**
 * is_single_dollar_sign - check if it is dollar sign
 * @curr_cmd: command that will by checked
 * @i: index of curr_cmd
 * Return: 1 if condition true or 0 otherwise
 */
int is_single_dollar_sign(char *curr_cmd, size_t i)
{
	return (curr_cmd[i] == '$' &&
		(curr_cmd[i + 1] == ' ' ||
		 curr_cmd[i + 1] == '\0'));
}

/**
 * is_errno - check if it is errno expansion
 * @curr_cmd: command that will by checked
 * @i: index of curr_cmd
 * Return: 1 if condition true or 0 otherwise
 */
int is_errno(char *curr_cmd, size_t i)
{
	return (curr_cmd[i] == '$' && curr_cmd[i + 1] == '?');
}

/**
 *  is_proccess_id - check if it is proccess id expansion
 * @curr_cmd: command that will by checked
 * @i: index of curr_cmd
 * Return: 1 if condition true or 0 otherwise
 */
int is_proccess_id(char *curr_cmd, size_t i)
{
	return (curr_cmd[i] == '$' && curr_cmd[i + 1] == '$');
}

/**
 * is_comment - check if it is comment
 * @curr_cmd: command that will by checked
 * @i: index of command
 * Return: 1 if condition true or 0 otherwise
 */
int is_comment(char *curr_cmd, size_t i)
{
	return ((curr_cmd[i] == ' ' &&
		 curr_cmd[i + 1] == '#') ||
		(curr_cmd[i] == '#' && i == 0));
}
