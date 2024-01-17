#include "shell.h"

/**
 * hsh - infinite loop that shows the prompt
 * @info: program information
 * @prompt: prompt to be printed
 */
void hsh(program_info_t *info, char *prompt)
{
	size_t curr_cmd_len = 0;
	int code = 0;

	while (++info->exec_counter)
	{
		_puts(prompt);

		code = curr_cmd_len = get_curr_cmd(info);
		if (code == EOF)
		{
			free_all_program_info(info);
			exit(errno);
		}

		if (curr_cmd_len >= 1)
		{
			expand_vars(info);
			tokenize_curr_cmd(info);
			expand_alias(info);
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
