#include "shell.h"

int is_interactive_mode(int ac);
int handle_signals(void);
void handle_ctrl_c_signal(int sig);

/**
 * main - entry point
 * @av: number of arguments.
 * @ac: array of pointers to the arguments.
 * @env: array of pointers to environment variables.
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
 * is_interactive_mode - is interactive mode
 * @ac: An array of pointers to the command-line arguments.
 * Return: 0 if condition true otherwise false
 */

int is_interactive_mode(int ac)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && ac == 1);
}

/**
 * handle_signals - handle signals
 * Return: 0 if success, 1 if failed
 */

int handle_signals(void)
{
	struct sigaction sig = {0};

	sig.sa_flags = SA_RESTART;
	sig.sa_handler = &handle_ctrl_c_signal;

	if (sigaction(SIGINT, &sig, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	return (0);
}

/**
 * handle_ctrl_c_signal - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @sig: option of the prototype
 */
void handle_ctrl_c_signal(int sig)
{
	(void)sig;
	_puts("\n");
	_puts(PROMPT);
}
