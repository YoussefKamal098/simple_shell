#include "shell.h"

void init_info_env(program_info_t *info, char **env);

/**
 * init_program_info - initial program information
 * @info: program information
 * @av: number of  arguments.
 * @ac: array of pointers to the arguments.
 * @env: array of pointers to environment variables.
 */
void init_program_info(program_info_t *info, int ac, char **av, char **env)
{
	info->name = av[0];

	if (ac == 1)
	{
		info->file_descriptor = STDIN_FILENO;
	}
	else
	{
		info->file_descriptor = open(av[1], O_RDONLY);
		if (info->file_descriptor == -1)
			print_open_file_error_msg(info, av[1]), exit(127);
	}

	if (env)
		init_info_env(info, env);
}

/**
 * init_info_env - initial the environment variables of program information
 * @info: program information
 * @env: array of pointers to environment variables.
 */
void init_info_env(program_info_t *info, char **env)
{
	size_t i;

	for (i = 0; env[i]; i++)
		list_push(&info->env, env[i]);
}
