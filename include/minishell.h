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
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

// === CONSTANTES ===
# define PROMPT "minishell> "
# define TRUE 1
# define FALSE 0

// === TIPOS DE TOKENS ===
typedef enum e_token_type
{
	TOKEN_WORD,		// palabra (comando o argumento)
	TOKEN_PIPE,		// |
	TOKEN_REDIR_IN,	// <
	TOKEN_REDIR_OUT,	// >
	TOKEN_REDIR_APPEND,	// >>
	TOKEN_HEREDOC,	// <<
	TOKEN_AND,		// && (bonus)
	TOKEN_OR,		// || (bonus)
	TOKEN_OPEN_PAR,	// ( (bonus)
	TOKEN_CLOSE_PAR	// ) (bonus)
}	t_token_type;

// === ESTRUCTURA DE UN TOKEN ===
typedef struct s_token
{
	t_token_type	type;
	char		*value;
	struct s_token	*next;
}	t_token;

// === TIPOS DE REDIRECCIÓN ===
typedef enum e_redir_type
{
	REDIR_IN,		// <
	REDIR_OUT,		// >
	REDIR_APPEND,	// >>
	REDIR_HEREDOC	// <<
}	t_redir_type;

// === ESTRUCTURA DE REDIRECCIÓN ===
typedef struct s_redir
{
	t_redir_type	type;
	char		*file;	// nombre del archivo o delimitador
	struct s_redir	*next;
}	t_redir;

// === ESTRUCTURA DE UN COMANDO ===
typedef struct s_cmd
{
	char		**argv;	// argumentos del comando
	t_redir		*redirs;	// lista de redirecciones
	struct s_cmd	*next;	// siguiente comando (en un pipe)
	int		pipe_in;	// fd para entrada
	int		pipe_out;	// fd para salida
}	t_cmd;

// === ESTRUCTURA DEL SHELL ===
typedef struct s_shell
{
	char		**env;		// copia del entorno
	struct termios	orig_termios;	// configuración original del terminal
	int		last_status;	// estado de salida del último comando
	t_token		*tokens;	// tokens de la línea de comando actual
	t_cmd		*cmd;		// comando actual en ejecución
	int		interactive;	// 1 si el shell es interactivo
}	t_shell;

// === VARIABLES GLOBALES ===
extern int g_signal_received;	// para manejar señales

// === FUNCIONES DE SHELL ===
int	main(int argc, char **argv, char **envp);
void	init_shell(t_shell *shell, char **envp);
int	shell_loop(t_shell *shell);
void	reset_terminal(t_shell *shell);

// === SIGNAL HANDLING ===
void	setup_signal_handlers(void);
void	ignore_signals(void);
void	default_signals(void);

// === LEXER Y PARSER ===
t_token	*tokenize_line(char *line);
void	add_token(t_token **tokens, t_token_type type, char *value);
t_token	*create_token(t_token_type type, char *value);
void	handle_quotes(char *line, int *i, char **word);
int	is_special_char(char c);

t_cmd	*parse_tokens(t_shell *shell, t_token *tokens);
int	parse_redirections(t_token **token_ptr, t_cmd *cmd);
int	syntax_check(t_token *tokens);
void	add_redirection(t_redir **redirs, t_redir_type type, char *file);
t_redir	*create_redirection(t_redir_type type, char *file);

// === EXPANSIÓN ===
void	expand_variables(t_shell *shell, char **word);
char	*get_var_value(t_shell *shell, char *var_name);
char	*expand_exit_status(t_shell *shell);

// === EXECUCIÓN ===
int	execute_cmd(t_shell *shell, t_cmd *cmd);
void	execute_pipe(t_shell *shell, t_cmd *cmd);
int	is_builtin(char *cmd);
int	exec_builtin(t_shell *shell, t_cmd *cmd);
int	handle_redirections(t_cmd *cmd);
void	reset_redirections(t_cmd *cmd, int stdin_fd, int stdout_fd);
pid_t	execute_process(t_shell *shell, t_cmd *cmd);
int	wait_for_process(pid_t pid);

// === BUILTINS ===
int	builtin_echo(t_shell *shell, char **argv);
int	builtin_cd(t_shell *shell, char **argv);
int	builtin_pwd(t_shell *shell, char **argv);
int	builtin_export(t_shell *shell, char **argv);
int	builtin_unset(t_shell *shell, char **argv);
int	builtin_env(t_shell *shell, char **argv);
int	builtin_exit(t_shell *shell, char **argv);
int	is_valid_identifier(char *str);

// === REDIRECCIONES ===
int	setup_redirections(t_cmd *cmd);
int	redirect_input(t_redir *redir);
int	redirect_output(t_redir *redir);
int	redirect_append(t_redir *redir);
int	redirect_heredoc(t_shell *shell, t_redir *redir);

// === UTILS ===
void	error_msg(const char *msg);
void	error_exit(const char *msg);
void	free_cmd(t_cmd *cmd);
void	free_tokens(t_token *tokens);
void	free_redirs(t_redir *redirs);
char	*get_cmd_path(const char *cmd, char **envp);
char	*get_env_value(t_shell *shell, const char *name);
void	print_error(const char *cmd, const char *arg, const char *msg);
char	**copy_env(char **envp);
int	add_env_var(t_shell *shell, char *var);
int	remove_env_var(t_shell *shell, char *var);

// === BONUS FUNCTIONS ===
char	*expand_wildcards(char *pattern);
int	execute_logic_ops(t_shell *shell, t_token *tokens);

#endif