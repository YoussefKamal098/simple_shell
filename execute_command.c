#include "shell.h"

/**
 * execute_command - execute a command with arguments.
 * @info: program information
 * Return: 0 if success error code otherwise
 */

int execute_command(program_info_t *info)
{
	int (*builtin_command)(program_info_t *info) = find_builtin_command(info);
	char *file_path, **curr_cmd_tokens, **env;
	int code, status;
	pid_t pid;

	if (builtin_command)
		return (builtin_command(info));
	code = find_program(info);
	if (code)
		return (code);

	env = list_to_strs(info->env);
	curr_cmd_tokens = list_to_strs(info->curr_cmd_tokens);
	file_path = get_node_str_at_index(info->curr_cmd_tokens, 0);

	pid = fork();
	if (pid == -1)
	{
		perror(info->curr_cmd_name), exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		code = execve(file_path, curr_cmd_tokens, env);
		if (code == -1)
			perror(info->curr_cmd_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			errno = 128 + WTERMSIG(status);
	}

	free_array_of_pointers(env);
	free_array_of_pointers(curr_cmd_tokens);
	return (0);
}
