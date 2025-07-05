#include "../include/minishell.h"

void	error_exit(char *msg)
{
	write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}
