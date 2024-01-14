#include "shell.h"

/**
 * _strlen - get length of string
 * @str: string
 * Return: length of string
 */

size_t _strlen(char *str)
{
	size_t i = 0;

	if (!str || *str == '\0')
		return (0);

	while (str[i])
		i++;

	return (i);
}

/**
 * _strcpy - copy source string to destination string
 * @dest: destination string
 * @src: source string
 * Return: copied string or NULL if dest or src is NULL
 */
char *_strcpy(char *dest, char *src)
{
	size_t i = 0;

	if (!dest || !src)
		return (NULL);

	while (src[i])
		dest[i] = src[i], i++;

	dest[i] = '\0';
	return (dest);
}

/**
 * strconcat - concatenate two strings
 * @str1: string
 * @str2: string
 * Return: concatenated string or NULL if malloc failed
 */

char *strconcat(char *str1, char *str2)
{
	size_t i, j, str_len = 0;
	char *str;

	if (!str1)
		str1 = "";
	if (!str2)
		str2 = "";

	str_len = _strlen(str1) + _strlen(str2);
	str = (char *)malloc(str_len + 1);
	if (!str)
	{
		errno = ENOMEM, perror("Error");
		return (NULL);
	}

	for (i = 0; str1[i] != '\0'; i++)
		str[i] = str1[i];
	for (j = 0; str2[j] != '\0'; i++, j++)
		str[i] = str2[j];

	str[i] = '\0';
	return (str);
}

/**
 * _strcmp - compare two strings
 * @str1: string
 * @str2: string
 * Return: 0 if equal positive number if str1 greater negative otherwise
 */

int _strcmp(char *str1, char *str2)
{
	size_t i;

	if (!str1 && !str2)
		return (0);

	if (!str1 || !str2)
	{
		if (!str1)
			return (-str2[0]);
		else
			return (str1[0]);
	}

	for (i = 0; str1[i] != '\0'; i++)
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);

	if (str1[i] == '\0' && str2[i] != '\0')
		return (-str2[i]);

	return (0);
}

/**
 * _strdup - duplicate string
 * @str: string
 * Return: duplicated string
 */

char *_strdup(char *str)
{
	size_t len = 0;
	char *str_dup;

	if (!str)
		return (NULL);

	len = _strlen(str);
	str_dup = (char *)malloc(len + 1);
	if (!str_dup)
	{
		errno = ENOMEM, perror("Error");
		return (NULL);
	}

	str_dup = _strcpy(str_dup, str);
	return (str_dup);
}
