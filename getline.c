#include "shell.h"

/**
 * _getline - read line from the file descriptor
 * @fd: file descriptor
 * @buff: buffer to store gotten input
 * @size: size of read bytes
 * Return: read bytes or -1 if it reach end of the file or
 * read operation failed
 */
int _getline(int fd, char *buff, size_t size)
{
	int read_bytes;

	read_bytes = read(fd, buff, size);

	if (read_bytes == -1)
		perror("Error");
	if (read_bytes == 0 || read_bytes == -1)
		return (EOF);

	return (read_bytes);
}
