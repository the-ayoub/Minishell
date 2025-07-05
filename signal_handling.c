#include "minishell.h"

volatile sig_atomic_t g_signal = 0;
int g_in_input_phase = 0;  // Variable global para estado de input

void sigint_handler(int sig)
{
    g_signal = sig;
    write(1, "\n", 1);
    if (g_in_input_phase) {
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void setup_signal_handlers(void)
{
    struct sigaction sa_int;
    
    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = SA_RESTART;  
    sigemptyset(&sa_int.sa_mask); 
    if (sigaction(SIGINT, &sa_int, NULL) == -1)
    {
        perror("minishell: sigaction");
        exit(EXIT_FAILURE);
    }
    signal(SIGQUIT, SIG_IGN);
}