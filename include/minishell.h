/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:46:54 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/31 22:20:33 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// === LIBRERÍAS ===
# include "../libft/inc/libft.h"
# include "ms_structs.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// === CONSTANTES ===
# define PROMPT "minishell> "
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1
# define PATH_MAX 4096

// === VARIABLES GLOBALES ===
extern volatile sig_atomic_t	g_in_input;

// === FUNCIONES DE SHELL ===
void						init_shell(t_shell *shell, char **envp);
int							shell_loop(t_shell *shell);

// === ENV AND LIST TOOLS ===
t_list						*env_lst_init(char **env);
char						**env_compiler(t_list *head);
int							generate_and_fill_arr(char ***arr, int i,
								t_list *lst);
void						set_env_var(t_shell *shell, const char *name,
								const char *value);

//	=== ENV UTILS ===
t_list						*locate_env_var(t_list *node, char *var);
char						*get_var_name(char *str);
int							update_env(t_shell *shell, char *arg);
int							is_valid_env_key(char *str);
int							check_var_and_del(t_list **head, char *var);

// === SIGNAL HANDLING ===
void						setup_signal_handlers(void);

// === SYNTAX CHECK ===
int							syntax_check(t_token *tokens);

// === PARSE TOKEN ===
int							parse_tokens(t_shell *shell, t_token *tokens,
								t_cmd **head);
// >>>	=== PARSE AUX
t_cmd						*create_new_command(void);
t_redir						*create_redirection(t_redir_type type, char *file);
void						add_argument(t_cmd *cmd, char *arg);
int							parse_pipe(t_token **current, t_cmd **cmd,
								t_cmd **ptr);

// === TOKENIZE ===
t_token						*tokenize_line(char *line);
t_token						*add_token(t_token **tokens, t_token_type type,
								char *value);
t_token						*create_token(t_token_type type, char *value);
void						delete_token(t_token **head, t_token *ptr);
// >>> TOKEN AUX
int							is_token_word(t_token_type type);
// >>> RETOKENIZE
int							retokenize(t_token **head);

// >>> COLLECT_WORD ===
int							collect_words(t_token **head, char *line, int *i,
								t_token_type *type);

// === EXPANSIÓN ===
int							expand_variables(t_shell *shell, t_token *head);
char						*assemble_expansion(char *token_value, \
							t_expand *dt);

// === EXPAND_UTILS ===
int							wrap_assamble_expansion(t_token **tkn, \
								t_expand *dt);
void						init_expand(t_expand *dt);
int							aux_upd_data(t_expand *dt, char *match,
								char *var_name, char *env_var);

// === EXECUCIÓN ===
int							execute_cmd(t_shell *shell, t_cmd *cmd);
pid_t						execute_process(t_shell *shell, t_cmd *cmd);
void						exec_external(t_shell *shell, t_cmd *cmd);

// === EXECUCIÓN UTILS ===
void						wrapper_single_command(t_shell *shell, t_cmd *cmd,
								int *pid);
void						wait_for_children(t_shell *shell, pid_t last_pid);
int							builtin_in_pipe(char *cmd);
void						close_pipe_ends(int pipe_fd[2], int keep_read_end);

// === EXEC PIPES ===
void						execute_pipe(t_shell *shell, t_cmd *cmd);

// === BUILTIN UTILS ===
int							is_builtin(char *cmd);
int							exec_builtin(t_shell *shell, t_cmd *cmd);
int							is_valid_identifier(char *str);

// === REDIR ===
int							setup_redirections(t_shell *shell, t_cmd *cmd);
int							reset_std_fds(int backup[2], t_shell *shell);
int							redirect_heredoc(t_shell *shell, t_redir *redir);
int							handle_heredoc_loop(int fd, const char *delimiter);

// === COMPLETED BUILTINS ===
int							builtin_echo(t_shell *shell, char **argv);
int							builtin_export(t_shell *shell, char **argv);
int							builtin_unset(t_shell *shell, char **argv);
int							builtin_cd(t_shell *shell, char **argv);
int							builtin_pwd(t_shell *shell, char **argv);
int							builtin_env(t_shell *shell, char **argv);
int							builtin_exit(t_shell *shell, char **argv);

// === WRAPPERS ===
int							wrapper_strjoin(char **s1, char *s2);
int							wrapper_dup(int *holder, int fd, t_shell *shell);
int							wrapper_dup2(int oldfd, int newfd, t_shell *shell);
t_token						*wrapper_exit(t_token **head);
void						wrapper_free_lst(t_list *head);

// === WRAPPERS 2 ===
void						free_wrapper(void **ptr);
int							waitpid_wrapper(pid_t *ptr, int *status);

// === FREE UTILS ===
void						free_cmd_list(t_cmd *head);
void						free_cmd(t_cmd *cmd);
void						free_tokens(t_token *tokens);
void						free_array(char **array);

// === UTILS ===
void						error_exit(char *msg);
void						free_array(char **array);
void						free_cmd(t_cmd *cmd);
void						free_tokens(t_token *tokens);
char						*get_cmd_path(const char *cmd, char **envp);
char						*get_env_value(t_shell *shell, const char *name);

// === DEBUGGING TOOLS ===
void						print_lst(t_list *ptr);

#endif
