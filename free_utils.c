#include "minishell.h"

void free_cmd_list(t_cmd *head)
{
    t_cmd *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free_cmd(tmp);
    }
}

void free_cmd(t_cmd *cmd)
{
    if (!cmd) return;
    
    // Liberar argumentos
    if (cmd->argv) {
        for (int i = 0; cmd->argv[i]; i++)
            free(cmd->argv[i]);
        free(cmd->argv);
    }
    
    // Liberar redirecciones
    t_redir *redir = cmd->redirs;
    while (redir) {
        t_redir *next = redir->next;
        if (redir->file) free(redir->file);
        free(redir);
        redir = next;
    }
    free(cmd);
}

void free_tokens(t_token *tokens)
{
    while (tokens) {
        t_token *next = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = next;
    }
}
