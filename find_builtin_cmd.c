#include "shell.h"

/**
 * find_builtin_cmd - find builtin command
 * @info: program information
 * Return: builtin function that execute the command or NULL if not found
 */

int (*find_builtin_cmd(program_info_t *info))(program_info_t *info)
{
	static builtin_cmd_t commands[] = {
	    {"exit", builtin_exit_cmd},
	    {"env", builtin_env_cmd},
	    {"setenv", builtin_setenv_cmd},
	    {"unsetenv", builtin_unsetenv_cmd},
	    {"cd", builtin_cd_cmd},
	    {"alias", builtin_alias_cmd},
	    {NULL, NULL}};
	size_t i;

	for (i = 0; commands[i].name; i++)
		if (_strcmp(info->curr_cmd_name, commands[i].name) == 0)
			return (commands[i].execute_func);

	return (NULL);
}
