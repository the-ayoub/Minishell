#include "../include/minishell.h"

void close_pipe_ends(int pipe_fd[2], int keep_read_end)
{
    if (pipe_fd[1] != -1)
        close(pipe_fd[1]);
    if (!keep_read_end && pipe_fd[0] != -1)
        close(pipe_fd[0]);
}

void wait_for_children(t_shell *shell, pid_t last_pid)
{
    int status;
    pid_t wpid;

    if (last_pid == -1)
        return;
    
    // Esperar por todos los procesos hijos
    while ((wpid = waitpid(-1, &status, 0)) > 0)
    {
        if (wpid == last_pid)
        {
            if (WIFEXITED(status))
                shell->last_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                shell->last_status = 128 + WTERMSIG(status);
        }
    }
}

int builtin_in_pipe(char *cmd)
{
    const char *pipe_builtins[] = {"echo", "env", "pwd", NULL};
    
    for (int i = 0; pipe_builtins[i]; i++)
        if (ft_strcmp(cmd, pipe_builtins[i]) == 0)
            return TRUE;
    return FALSE;
}