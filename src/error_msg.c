#include "../include/minishell.h"

void	error_msg(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
