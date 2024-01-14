#include "shell.h"

/**
 * execute_cmd - execute the command with arguments.
 * @info: program information
 * Return: 0 if success or error code otherwise
 */

int execute_cmd(program_info_t *info)
{
	int (*builtin_cmd)(program_info_t *info);
	char *file_path, **curr_cmd_tokens, **env;
	int code, status;
	pid_t pid;

	builtin_cmd = find_builtin_cmd(info);
	if (builtin_cmd)
		return (builtin_cmd(info));

	code = find_program(info);
	if (code)
		return (code);

	env = dict_to_strs(info->env, "=");
	curr_cmd_tokens = list_to_strs(info->curr_cmd_tokens);
	file_path = get_list_node_value_at_index(info->curr_cmd_tokens, 0);

	pid = fork();
	if (pid == -1)
		perror(info->curr_cmd_name), exit(EXIT_FAILURE);

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

	free_pointers_arr(env);
	free_pointers_arr(curr_cmd_tokens);
	return (0);
}
