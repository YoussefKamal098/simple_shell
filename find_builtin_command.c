#include "shell.h"

/**
 * find_builtin_command - find builtin command
 * @info: program information
 * Return: builtin function that execute the command or NULL if not found
 */

int (*find_builtin_command(program_info_t *info))(program_info_t *info)
{
	static builtin_command_t commands[] = {
	    {"exit", builtin_exit_command},
	    {"env", builtin_env_command},
	    {"setenv", builtin_set_env},
	    {"unsetenv", builtin_unset_env},
	    {NULL, NULL}};
	size_t i;

	for (i = 0; commands[i].name; i++)
		if (_strcmp(info->curr_cmd_name, commands[i].name) == 0)
			return (commands[i].execute_func);

	return (NULL);
}
