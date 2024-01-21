#include "shell.h"

/**
 * _getline - read line from the file descriptor
 * @fd: file descriptor
 * @buffer: buffer to store gotten input
 * @size: size of read bytes
 * Return: read bytes or -1 if it reach end of the file or
 * read operation failed
 */
int _getline(int fd, char *buffer, size_t size)
{
	int read_bytes, i;

	read_bytes = read(fd, buffer, size);

	if (read_bytes == -1)
		perror("Error");
	if (read_bytes == 0 || read_bytes == -1)
		return (EOF);

	for (i = 0; i < read_bytes; i++)
	{
		if (buffer[i] == '\n')
		{
			lseek(fd, -(read_bytes - i - 1), SEEK_CUR);
			break;
		}
	}

	read_bytes = i != read_bytes ? i : read_bytes;
	buffer[read_bytes] = '\0';

	return (read_bytes);
}
