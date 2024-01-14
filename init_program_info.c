#include "shell.h"

void init_info_env(program_info_t *info, char **env);

/**
 * init_program_info - initial program information
 * @info: program information
 * @ac: number of  arguments.
 * @av: arguments of program
 * @env: environment variables.
 */
void init_program_info(program_info_t *info, int ac, char **av, char **env)
{
	info->name = av[0];

	if (ac == 1)
		info->fd = STDIN_FILENO;
	else
	{
		info->fd = open(av[1], O_RDONLY);
		if (info->fd == -1)
			print_open_file_err_msg(info, av[1]), exit(127);
	}

	if (env)
		init_info_env(info, env);
}

/**
 * init_info_env - initial the environment variables of program information
 * @info: program information
 * @env: array of strings to environment variables.
 */
void init_info_env(program_info_t *info, char **env)
{
	char *key, *value;
	size_t i, j;

	(void)key;
	(void)value;

	for (i = 0; env[i]; i++)
	{
		j = get_delimiter_index(env[i], "=");

		env[i][j] = '\0';
		if (env[i][j + 1] != '\0')
			dict_push(&info->env, &env[i][0], &env[i][j + 1]);
	}
}
