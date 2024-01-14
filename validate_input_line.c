#include "shell.h"

int check_for_syntax_err(program_info_t *info, char *input_line);
int check_for_unsupported_features(program_info_t *info, char *input_line);
int is_single_char_operator(char *input_line, size_t i);

/**
 * validate_input_line - validate input_line
 * @info: program information
 * @input_line: input line that will by checked
 * Return: 1 if input ine is invalid 0 otherwise
 */

int validate_input_line(program_info_t *info, char *input_line)
{
	if (check_for_syntax_err(info, input_line))
		return (1);
	if (check_for_unsupported_features(info, input_line))
		return (1);

	return (0);
}

/**
 * check_for_syntax_err - check for syntax error
 * @info: program information
 * @inputline: input line that will by checked
 * Return: return 1 id there is syntax error 0 otherwise
 */

int check_for_syntax_err(program_info_t *info, char *inputline)
{
	size_t i, j = 0;
	char curr_cmd[BUFF_SIZE], ch;

	for (i = 0; inputline[i]; i++)
	{
		if (is_and_operator(inputline, i) || is_or_operator(inputline, i))
		{
			curr_cmd[j] = '\0';
			if (is_empty_str(curr_cmd))
			{
				errno = 2;
				print_syntax_err_msg(info, inputline[i] == '&' ? "&&" : "||");
				return (-1);
			}

			i++, j = 0;
		}
		else if (is_double_semicolon(inputline, i))
		{
			print_syntax_err_msg(info, ";;");
			return (1);
		}
		else if (is_single_char_operator(inputline, i))
		{
			curr_cmd[j] = '\0';
			if (is_empty_str(curr_cmd))
			{
				ch = inputline[i];
				errno = 2;
				print_syntax_err_msg(info, &ch);
				return (-1);
			}
			j = 0;
		}
		else
			curr_cmd[j] = inputline[i], j++;
	}

	return (0);
}

/**
 * check_for_unsupported_features - check for unsupported features
 * @info: program information
 * @input_line: input line that will by checked
 * Return: return 1 id there is syntax error 0 otherwise
 */

int check_for_unsupported_features(program_info_t *info, char *input_line)
{
	size_t i;
	char *temp;

	for (i = 0; input_line[i]; i++)
	{
		if (is_and_operator(input_line, i) || is_or_operator(input_line, i))
		{
			i++;
			continue;
		}
		else if (input_line[i] == '|' || input_line[i] == '&')
		{
			if (input_line[i] == '|')
				temp = "Pipe";
			else
				temp = "Background proccess";

			print_unsupported_feature_err_msg(info, temp);
			return (-1);
		}
	}

	return (0);
}

/**
 * is_single_char_operator - check for | & ; operator
 * @input_line: input_line that will by checked
 * @i: index of input_line
 * Return: 1 if condition true 0 otherwise
 */
int is_single_char_operator(char *input_line, size_t i)
{
	return (input_line[i] == '|' ||
		input_line[i] == '&' ||
		input_line[i] == ';');
}
