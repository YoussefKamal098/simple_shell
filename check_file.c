#include "shell.h"

int is_file_or_dir_exist(char *path, struct stat *file_info);
int is_file_and_executable(char *path, struct stat *file_info);
int is_file(struct stat *file_info);
int is_executable(char *path);

/**
 * check_file - checks if the file exists and not a directory,
 * and it has execution permissions.
 * @path: path of the file
 * Return: 0 on success or error code otherwise
 */
int check_file(char *path)
{
	struct stat file_info;

	if (is_file_or_dir_exist(path, &file_info))
		return (is_file_and_executable(path, &file_info));

	errno = CMD_NOT_FOUND;
	return (errno);
}

/**
 * is_file_or_dir_exist - checks if the file or the directory exist,
 * @path: path of the file
 * @file_info: file info
 * Return: 1 if condition true 0 otherwise
 */

int is_file_or_dir_exist(char *path, struct stat *file_info)
{
	return (stat(path, file_info) != -1);
}

/**
 * is_file_and_executable - check if it is a file and executable
 * @path: path of the file
 * @file_info: file information
 * Return: 0 if condition true or error code otherwise
 */

int is_file_and_executable(char *path, struct stat *file_info)
{
	if (!is_file(file_info) || !is_executable(path))
	{
		errno = PERMISSION_DENIED;
		return (errno);
	}

	return (0);
}

/**
 * is_file - check if it is a file
 * @file_info: file information
 * Return: 1 if condition true or 0 otherwise
 */

int is_file(struct stat *file_info)
{
	return (S_ISDIR(file_info->st_mode) == 0);
}

/**
 * is_executable - check if it the file or directory executable
 * @path: path of the file
 * Return:1 if condition true 0 or otherwise
 */

int is_executable(char *path)
{
	return (access(path, X_OK) == 0);
}
