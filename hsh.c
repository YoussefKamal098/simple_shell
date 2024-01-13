#include "shell.h"

/**
 * hsh - infinite loop that shows the prompt
 * @info: program information
 * @prompt: prompt to be printed
 */
void hsh(program_info_t *info, char *prompt)
{
	int code = 0;
	size_t cmd_len = 0;

	while (1)
	{
		_puts(prompt);
		info->exec_counter += 1;

		code = cmd_len = _getline(info);
		if (code == EOF)
		{
			free_all_program_info(info);
			exit(errno);
		}

		if (cmd_len >= 1)
		{
			expand_vars(info);
			tokenize_curr_cmd(info);
			if (info->curr_cmd_tokens)
			{
				code = execute_cmd(info);
				if (code != 0)
					print_stderr_msg(info, code);
			}
		}

		free_curr_program_info(info);
	}
}
