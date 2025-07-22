/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:46:54 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/22 21:56:40 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// === LIBRERÍAS ===
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/inc/libft.h"
# include "ms_structs.h"

// === CONSTANTES ===
# define PROMPT "minishell> "
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1
# define PATH_MAX 4096  // Tamaño razonable para la mayoría de sistemas


// === VARIABLES GLOBALES ===
typedef struct s_global
{
    volatile sig_atomic_t	received;
    int						in_input;
}							t_global;

extern volatile t_global g_state;

// === FUNCIONES DE SHELL ===
int		main(int argc, char **argv, char **envp);
void	init_shell(t_shell *shell, char **envp);
int		shell_loop(t_shell *shell);

// === LIST TOOLS ===
void	wrapper_free_lst(t_list *head);

// === ENV AND LIST TOOLS ===
t_list	*env_lst_init(char **env);
char	**env_compiler(t_list *head);
int		generate_and_fill_arr(char ***arr, int i, t_list *lst);
void	set_env_var(t_shell *shell, const char *name, const char *value);
int		add_env_var(t_shell *shell, char *var);
int		remove_env_var(t_shell *shell, char *var);

//	|||	=== ENV UTILS ===
t_list	*locate_env_var(t_list *node, char *var);
char	*get_var_name(char *str);
int		update_env(t_shell *shell, char *arg);
int		is_valid_env_key(char *str);

// === SIGNAL HANDLING ===
void	setup_signal_handlers(void);
void	sigint_handler(int sig);

// LEXER Y PARSER

// === SYNTAX CHECK ===
int		syntax_check(t_token *tokens);

// === PARSE TOKEN ===
int		parse_tokens(t_shell *shell, t_token *tokens, t_cmd **head);
// >>>	=== PARSE AUX
t_cmd	*create_new_command(void);
t_redir	*create_redirection(t_redir_type type, char *file);
void	add_argument(t_cmd *cmd, char *arg);
int		parse_pipe(t_token **current, t_cmd **cmd, t_cmd **ptr);

// === TOKENIZE ===
t_token	*tokenize_line(char *line);
t_token	*add_token(t_token **tokens, t_token_type type, char *value);
t_token	*create_token(t_token_type type, char *value);
void	delete_token(t_token **head, t_token *ptr);
// >>> TOKEN AUX
int		is_token_word(t_token_type type);
// >>> RETOKENIZE
int		retokenize(t_token **head);

// >>>	=== COLLECT_WORD ===
int	collect_words(t_token **head, char *line, int *i, t_token_type *type);

// END LEXER Y PARSER

// === EXPANSIÓN ===
int		expand_variables(t_shell *shell, t_token *head);
void	append_char(char **str, char c);
int		expand_dollar(t_shell *shell, char **result, char *ptr);

// === EXECUCIÓN ===
int		execute_cmd(t_shell *shell, t_cmd *cmd);
void	execute_pipe(t_shell *shell, t_cmd *cmd);
int		is_builtin(char *cmd);
int		exec_builtin(t_shell *shell, t_cmd *cmd);
int		setup_redirections(t_shell *shell, t_cmd *cmd);
int		reset_std_fds(int backup[2]);
pid_t	execute_process(t_shell *shell, t_cmd *cmd);
void	close_pipe_ends(int pipe_fd[2], int keep_read_end);
void	wait_for_children(t_shell *shell, pid_t last_pid);
int		builtin_in_pipe(char *cmd);
int		redirect_heredoc(t_shell *shell, t_redir *redir);
void	exec_external(t_shell *shell, t_cmd *cmd);

// === COMPLETED BUILTINS ===
int		builtin_echo(t_shell *shell, char **argv);

// === PENDING BUILTINS ===
int		builtin_unset(t_shell *shell, char **argv);
int		builtin_cd(t_shell *shell, char **argv);
int		builtin_pwd(t_shell *shell, char **argv);
int		builtin_export(t_shell *shell, char **argv);
int		builtin_env(t_shell *shell, char **argv);
int		builtin_exit(t_shell *shell, char **argv);
int		is_valid_identifier(char *str);
int		is_valid_exit_arg(char *arg);

// === WRAPPERS ===
int	wrapper_strjoin(char **s1, char *s2);
int	wrapper_dup(int *holder, int fd, t_shell *shell);
int	wrapper_dup2(int oldfd, int newfd, t_shell *shell);

// === UTILS ===
void	error_msg(const char *msg);
void	error_exit(char *msg);
void	free_array(char **array);
void	free_cmd(t_cmd *cmd);
void	free_tokens(t_token *tokens);
void	free_redirs(t_redir *redirs);
char	*get_cmd_path(const char *cmd, char **envp);
char	*get_env_value(t_shell *shell, const char *name);
void	free_cmd_list(t_cmd *head);

// === DEBUGGING TOOLS ===
void	expand_arr_and_print(t_list *lst);
void	print_arr(char **str);
void	print_lst(t_list *ptr);

// xxxx Deprecated xxxx
char	**copy_env(char **envp);
void	expand_exit_status(t_shell *shell, char **result);

#endif
