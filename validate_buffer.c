#include "shell.h"

/**
 * check_for_syntax_err - check for syntax error
 * @info: program information
 * @buffer: buffer that will by checked
 * Return: return 1 id there is syntax error 0 otherwise
 */

int check_for_syntax_err(program_info_t *info, char *buffer)
{
	size_t i, j = 0;
	char cmd[BUFFER_SIZE], ch;

	for (i = 0; buffer[i]; i++)
	{
		if (is_and_operator(buffer, i) || is_or_operator(buffer, i))
		{
			cmd[j] = '\0';
			if (is_empty_str(cmd))
			{
				print_syntax_err_msg(info, buffer[i] == '&' ? "&&" : "||");
				return (1);
			}

			i++, j = 0;
		}
		else if (is_double_semicolon(buffer, i))
		{
			print_syntax_err_msg(info, ";;");
			return (1);
		}
		else if (buffer[i] == '|' || buffer[i] == '&' || buffer[i] == ';')
		{
			cmd[j] = '\0';
			if (is_empty_str(cmd))
			{
				ch = buffer[i], print_syntax_err_msg(info, &ch);
				return (1);
			}
			j = 0;
		}
		else
			cmd[j] = buffer[i], j++;
	}

	return (0);
}

/**
 * check_for_unsupported_features - check for unsupported features
 * @info: program information
 * @buffer: buffer that will by checked
 * Return: return 1 id there is syntax error 0 otherwise
 */

int check_for_unsupported_features(program_info_t *info, char *buffer)
{
	size_t i;
	char *temp;

	for (i = 0; buffer[i]; i++)
	{
		if (is_and_operator(buffer, i) || is_or_operator(buffer, i))
		{
			i++;
			continue;
		}
		else if (buffer[i] == '|' || buffer[i] == '&')
		{
			if (buffer[i] == '|')
				temp = "Pipe";
			else
				temp = "Background proccess";

			print_unsupported_feature_err_msg(info, temp);
			return (1);
		}
	}

	return (0);
}
