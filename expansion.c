#include "shell.h"

int buffer_add(char *buffer, char *str);
char *get_env_key_from_buffer(char *buffer, size_t *i);
int is_dollar_sign(char *buffer, size_t i);

/**
 * expand_variables - expand variables
 * @info: program information
 */
void expand_variables(program_info_t *info)
{
	size_t i, j = 0;
	char curr_cmd_expansion[BUFFER_SIZE] = {'\0'}, *temp, *expansion;
	char *curr_cmd = info->curr_cmd;

	if (curr_cmd[0] == '#')
	{
		free(curr_cmd);
		info->curr_cmd = _strdup(" ");
		return;
	}

	for (i = 0; curr_cmd[i]; i++)
	{
		if (curr_cmd[i] == ' ' && curr_cmd[i + 1] == '#')
			break;
		else if (curr_cmd[i] == '$' && curr_cmd[i + 1] == '?')
		{
			expansion = _itoa(errno, 1);
			j = buffer_add(curr_cmd_expansion, expansion), free(expansion), i++;
		}
		else if (curr_cmd[i] == '$' && curr_cmd[i + 1] == '$')
		{
			expansion = _itoa(getpid(), 1);
			j = buffer_add(curr_cmd_expansion, expansion), free(expansion), i++;
		}
		else if (curr_cmd[i] == '$' && !is_dollar_sign(curr_cmd, i))
		{
			temp = get_env_key_from_buffer(curr_cmd, &i);
			expansion = get_env_key(info, temp), free(temp);
			if (expansion)
				j = buffer_add(curr_cmd_expansion, expansion), free(expansion);
		}
		else
			curr_cmd_expansion[j] = curr_cmd[i], j++;
	}

	if (_strcmp(curr_cmd, curr_cmd_expansion))
		free(curr_cmd), info->curr_cmd = _strdup(curr_cmd_expansion);
}

/**
 * get_env_key_from_buffer - get environment variable key from buffer
 * @buffer: string that environment variable key extract from it
 * @i: start index of key in buffer
 * Return: the environment variable key
 */
char *get_env_key_from_buffer(char *buffer, size_t *i)
{
	size_t j, k, flag = 0;
	char key[BUFFER_SIZE], delimiters[] = {'$', '\n', ' ', '"', '\'', '\0'};

	*i = *i + 1;
	for (j = 0; buffer[*i]; j++)
	{
		for (k = 0; delimiters[k]; k++)
		{
			if (buffer[*i] == delimiters[k])
			{
				flag = 1;
				break;
			}
		}

		if (flag)
			break;

		key[j] = buffer[*i], *i = *i + 1;
	}

	*i = *i - 1, key[j] = '\0';
	return (_strdup(key));
}

/**
 * is_dollar_sign - check if is dollar sign or not
 * @buffer: buffer that will by checked
 * @i: index of buffer
 * Return: 1 if condition true 0 otherwise
 */
int is_dollar_sign(char *buffer, size_t i)
{
	return (buffer[i] == '$' && (buffer[i + 1] == ' ' || buffer[i + 1] == '\0'));
}

/**
 * buffer_add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str: string to by added to buffer
 * Return: last index of buffer
 */
int buffer_add(char *buffer, char *str)
{
	int len, i;

	len = _strlen(buffer);
	if (!str || *str == '\0')
		return (len);

	for (i = 0; str[i]; i++)
		buffer[len + i] = str[i];

	return (len + i);
}
