#include "shell.h"

void handle_ctrl_c_signal(int sig);

/**
 * handle_signals - handle signals
 * Return: 0 if success or 1 if it failed
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
