#include "shell.h"

/**
 * _puts - print string to standard output
 * @str: string
 * Return: number of written bytes or -1 if fails to write
 */

int _puts(char *str)
{
	int bytes = write(STDOUT_FILENO, str, _strlen(str));

	if (bytes == -1)
		perror("Error writing to the file");

	return (bytes);
}
