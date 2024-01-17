#include "shell.h"

/**
 * is_starts_with - is string starts with prefix
 * @str: string
 * @prefix: prefix
 * Return: 1 if string starts with prefix or 0 otherwise
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
 * Return: number of digits
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
 * _isdigit - check if character is digit
 * @ch: character
 * Return: 1 if the characters is digit or 0 otherwise
 */
int _isdigit(char ch)
{
	return (ch >= '0' && ch <= '9');
}

/**
 * get_substr_from_to - get substring form index i to index j
 * @str: string
 * @start:start index
 * @end:end index
 * Return: substring or NULL if str is NULL or
 * i greater than j or j greater that str length
 */

char *get_substr_from_to(char *str, size_t start, size_t end)
{
	size_t dest_idx, src_idx, substr_len;
	char *sub_str;

	if (!str || start > end || _strlen(str) < end)
		return (NULL);

	substr_len = end - start + 1;
	sub_str = (char *)malloc(substr_len + 1);
	if (!sub_str)
	{
		errno = ENOMEM, perror("Error");
		return (NULL);
	}

	dest_idx = 0;
	for (src_idx = start; src_idx < end && str[src_idx]; src_idx++, dest_idx++)
		sub_str[dest_idx] = str[src_idx];

	sub_str[dest_idx] = '\0';
	return (sub_str);
}
