#include "shell.h"

char *skip_delimiters(char *str, char *delims);

/**
 * _strtok - separate string with specific delimiters
 * @str: string
 * @delims: delimiters
 * Return: sub string of string
 */

char *_strtok(char *str, char *delims)
{
	static char *strcopy;
	char *substr;
	size_t i;
	int flag;

	if (str)
		strcopy = skip_delimiters(str, delims);

	if (*strcopy == '\0')
		return (NULL);

	substr = strcopy;

	for (; *strcopy; strcopy++)
	{
		flag = 0;
		for (i = 0; delims[i]; i++)
		{
			if (*strcopy == delims[i])
			{
				*strcopy = '\0';
				strcopy++;
				flag = 1;
				break;
			}
		}

		if (flag)
		{
			strcopy = skip_delimiters(strcopy, delims);
			break;
		}
	}

	return (substr);
}

/**
 * skip_delimiters - skip string delimiters
 * @str: string
 * @delims: delimiters
 * Return: string
 */

char *skip_delimiters(char *str, char *delims)
{
	size_t i;
	int flag;

	for (; *str; str++)
	{
		flag = 1;
		for (i = 0; delims[i]; i++)
		{
			if (*str == delims[i])
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
