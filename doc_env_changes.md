
# Changes for env
from    char **
to      t_list

## STRUCT
char    **env

to

t_list  *env

## DIFF IN LIBFT_BONUS

### IMPLEMENTATION

/************ ENV ************/

/* ENV_MAIN */
void	create_env_var(t_minishell *data, char *buffer);
t_list	*env_lst_init(char **env);

/* ENV_STR_TOOLS */
int		is_var_name_ok(char *str);
size_t	get_var_len(char *str);
char	*ft_strdup_env(const char *src);

/* ENV_PARSING */

    WARNING: MALLOC
char	*get_var_name(char *str);
char	**expand_env_var(char *var);

    FUNCTION FREES MEMORY
void	search_and_print_env_var(t_minishell *data, char *str);

    NO MALLOC
char	*locate_env_var(t_minishell *data, char *str);

/* FREE MEMORY */
void	free_split_wrp(char **str);
void	free_lst_wrp(t_list *head);

