#include "shell.h"

char *skip_delimiters(char *str, char *delimiters);

/**
 * _strtok - separate string with specific delimiters
 * @str: string
 * @delims: delimiters
 * Return: sub string of string
 */

char *_strtok(char *str, char *delims)
{
	static char *str_copy;
	char *substr;
	size_t i;
	int flag;

	if (str)
		str_copy = skip_delimiters(str, delims);

	if (*str_copy == '\0')
		return (NULL);

	substr = str_copy;

	for (; *str_copy; str_copy++)
	{
		flag = 0;
		for (i = 0; delims[i]; i++)
		{
			if (*str_copy == delims[i])
			{
				*str_copy = '\0';
				str_copy++;
				flag = 1;
				break;
			}
		}

		if (flag)
		{
			str_copy = skip_delimiters(str_copy, delims);
			break;
		}
	}

	return (substr);
}

/**
 * skip_delimiters - skip string delimiters
 * @str: string
 * @delimiters: delimiters
 * Return: string
 */

char *skip_delimiters(char *str, char *delimiters)
{
	size_t i;
	int flag;

	for (; *str; str++)
	{
		flag = 1;
		for (i = 0; delimiters[i]; i++)
		{
			if (*str == delimiters[i])
			{
				*str = '\0';
				flag = 0;
				break;
			}
		}

		if (flag)
			break;
	}

	return (str);
}
