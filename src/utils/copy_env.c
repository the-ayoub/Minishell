#include "minishell.h"

char	**copy_env(char **envp)
{
    int i;
    char **copy_envp;

    i = 0;
    while(envp[i])
        i++;
    copy_envp = malloc((i + 1) * sizeof(char *));
    if(!copy_envp)
        return(NULL);
    i = 0;
    while(envp[i])
    {
        copy_envp[i] = ft_strdup(envp[i]);
        if(!copy_envp[i])
        {
            free_array(copy_envp);
            return(NULL);
        }
        i++;
    }
    copy_envp[i] = NULL;
    return(copy_envp);
}
