#include "shell.h"

int is_interactive_mode(int ac);

/**
 * main - entry point of program
 * @ac: number of arguments.
 * @av: array of strings to the arguments.
 * @env: array of strings to environment variables.
 * Return: always 0
 */

int main(int ac, char **av, char **env)
{
	program_info_t info = PROGRAM_INFO_INIT;
	char *prompt = "";

	init_program_info(&info, ac, av, env);
	handle_signals();

	if (is_interactive_mode(ac))
		prompt = PROMPT;

	errno = 0;
	hsh(&info, prompt);
	return (0);
}

/**
 * is_interactive_mode - check if it is interactive mode
 * @ac: number of arguments.
 * Return: 1 if condition true or 0 otherwise
 */

int is_interactive_mode(int ac)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && ac == 1);
}
