#include "shell.h"

/**
 * is_starts_with - is string starts with prefix
 * @str: string
 * @prefix: prefix string
 * Return: 1 if str starts with prefix 0 otherwise
 */
int is_starts_with(char *str, char *prefix)
{
	if (!str || !prefix)
		return (1);

	while (*prefix)
		if (*prefix++ != *str++)
			return (0);
	return (1);
}

/**
 * count_digit - count number digit
 * @num: number
 * Return: length of number
 */

size_t count_digit(size_t num)
{
	size_t len = 0;

	while (num)
	{
		num /= 10;
		len++;
	}

	return (len);
}

/**
 * _isdigit - _isdigit
 * @c: c
 * Return: 1 if characters is digit 0 otherwise
 */
int _isdigit(char c)
{
	return (c >= '0' && c <= '9');
}
