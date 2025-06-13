#include "minishell.h"

int	shell_loop(t_shell *shell)
{
    char *line;

    
    while(1)
    {
        line = readline(PROMPT);
        if(!line)
            break;
        if(line)
            add_history(line);
        shell->tokens = tokenize_line(line);
        if(syntax_check(shell->tokens))
            shell->cmd = parse_tokens(shell,shell->tokens);
        if(shell->cmd)
            execute_pipe(shell,shell->cmd);
        free(line);
        free_cmd(shell->cmd);
        free_tokens(shell->tokens);
        shell->cmd = NULL;
        shell->tokens= NULL;
    }
}