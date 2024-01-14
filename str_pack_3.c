#include "shell.h"

/**
 * str_n_concat - concatenate multiple string in one string
 * @num: number of string
 * Return: concatenated string or NULL if malloc failed
 */

char *str_n_concat(size_t num, ...)
{
	size_t i, str_len = 0;
	char **strs, *str, *temp;
	va_list args;

	strs = (char **)malloc(sizeof(char *) * num);
	if (!strs)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	va_start(args, num);
	for (i = 0; i < num; i++)
	{
		strs[i] = va_arg(args, char *);
		str_len += _strlen(strs[i]);
	}

	va_end(args);

	str = (char *)malloc(str_len + 1);
	if (!str)
	{
		errno = ENOMEM;
		perror("Error");
		free(strs);
		return (NULL);
	}

	temp = str;
	for (i = 0; i < num; i++)
	{
		_strcpy(str, strs[i]);
		str += _strlen(strs[i]);
	}

	*str = '\0';
	free(strs);
	return (temp);
}

/**
 * is_space - check if string sequence of spaces
 * @str: string
 * Return: 1 if condition true or 0 if condition false -1 if str is NULL
 */

int is_space(char *str)
{
	size_t i;

	if (!str)
		return (-1);

	for (i = 0; str[i]; i++)
		if (str[i] != ' ')
			return (0);
	return (1);
}

/**
 * is_empty_str - check if string is empty string
 * @str: string
 * Return: 1 if condition true 0 if condition false -1 if str is NULL
 */

int is_empty_str(char *str)
{
	if (!str)
		return (0);

	return (str[0] == '\0' || is_space(str));
}

/**
 * get_delimiter_index - get delimiter index of string
 * @str: string
 * @delims: delimiters
 * Return: index of first delimiter or -1 if delimiter doesn't exist
 */

int get_delimiter_index(char *str, char *delims)
{
	size_t i, j;

	if (!str || !delims)
		return (-1);

	for (i = 0; str[i]; i++)
		for (j = 0; delims[j]; j++)
			if (str[i] == delims[j])
				return (i);

	return (-1);
}

/**
 * add_buffer - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str: string to by added to buffer
 * Return: last index of buffer
 */
int add_buffer(char *buffer, char *str)
{
	int len, i;

	len = _strlen(buffer);
	if (!str || *str == '\0')
		return (len);

	for (i = 0; str[i]; i++)
		buffer[len + i] = str[i];

	return (len + i);
}
