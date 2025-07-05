#include "minishell.h"

void expand_exit_status(t_shell *shell, char **result)
{
    char *exit_str = ft_itoa(shell->last_status);
    char *new_result = ft_strjoin(*result, exit_str);
    free(*result);
    free(exit_str);
    *result = new_result;
}

void expand_variables(t_shell *shell, char **word)
{
    char *result = ft_strdup("");
    char *ptr = *word;
    int in_squote = 0;
    int in_dquote = 0;

    while (*ptr) {
        if (*ptr == '\'' && !in_dquote) 
            in_squote = !in_squote;
        else if (*ptr == '"' && !in_squote) 
            in_dquote = !in_dquote;
        else if (*ptr == '$' && !in_squote) {
            if (ptr[1] == '?') {
                expand_exit_status(shell, &result);
                ptr += 2;
                continue;
            }
            // ... (expansión de variables normales)
        }
        char str[2] = {*ptr, '\0'};
        char *new_temp = ft_strjoin(result, str);
        free(result);
        result = new_temp;
        ptr++;
    }
    free(*word);
    *word = result;
}
