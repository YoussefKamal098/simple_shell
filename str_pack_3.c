#include "shell.h"

/**
 * str_n_concat - concatenate multiple string in one string
 * @n: number of string
 * Return:concatenated string or NULL if malloc failed
 */
char *str_n_concat(unsigned int n, ...)
{
	size_t i, str_len = 0;
	char **strs, *str, *temp;
	va_list args;

	strs = (char **)malloc(sizeof(char *) * n);
	if (!strs)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	va_start(args, n);
	for (i = 0; i < n; i++)
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
	for (i = 0; i < n; i++)
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
 * Return: 1 if condition true 0 if condition false -1 if str is NULL
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
