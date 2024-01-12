#include "shell.h"

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
