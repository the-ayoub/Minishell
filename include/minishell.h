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
# include "../libft/libft.h"

// === CONSTANTES ===
# define PROMPT "minishell> "
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1
# define PATH_MAX 4096  // Tamaño razonable para la mayoría de sistemas

// Estados para el análisis de comillas
typedef enum e_parse_state
{
    STATE_GENERAL,
    STATE_IN_SQUOTE,
    STATE_IN_DQUOTE
} t_parse_state;

// === TIPOS DE TOKENS ===
typedef enum e_token_type
{
	TOKEN_WORD,         // palabra (comando o argumento)
	TOKEN_PIPE,         // |
	TOKEN_REDIR_IN,     // <
	TOKEN_REDIR_OUT,    // >
	TOKEN_REDIR_APPEND, // >>
	TOKEN_HEREDOC,      // <<
}	t_token_type;

// === ESTRUCTURA DE UN TOKEN ===
typedef struct s_token
{
	t_token_type	type;
	char		    *value;
	struct s_token	*next;
}	t_token;

// === TIPOS DE REDIRECCIÓN ===
typedef enum e_redir_type
{
	REDIR_IN,       // <
	REDIR_OUT,      // >
	REDIR_APPEND,   // >>
	REDIR_HEREDOC   // <<
}	t_redir_type;

// === ESTRUCTURA DE REDIRECCIÓN ===
typedef struct s_redir
{
	t_redir_type	type;
	char		    *file;  // nombre del archivo o delimitador
	struct s_redir	*next;
}	t_redir;

// === ESTRUCTURA DE UN COMANDO ===
typedef struct s_cmd
{
	char		**argv;     // argumentos del comando
	t_redir		*redirs;    // lista de redirecciones
	struct s_cmd	*next;  // siguiente comando (en un pipe)
}	t_cmd;

// === ESTRUCTURA DEL SHELL ===
typedef struct s_shell
{
	char		**env;              // copia del entorno
	struct termios	orig_termios;   // configuración original del terminal
	int		last_status;        // estado de salida del último comando
	t_token		*tokens;            // tokens de la línea de comando actual
	t_cmd		*cmd;               // comando actual en ejecución
	int		interactive;        // 1 si el shell es interactivo
	int     in_input_phase;  // Nuevo: para manejo de señales
}	t_shell;

// === VARIABLES GLOBALES ===
typedef struct s_global
{
    volatile sig_atomic_t received;
    int in_input;
} t_global;
extern volatile t_global g_state;

// === FUNCIONES DE SHELL ===
int		main(int argc, char **argv, char **envp);
void	init_shell(t_shell *shell, char **envp);
int		shell_loop(t_shell *shell);

// === SIGNAL HANDLING ===
void	setup_signal_handlers(void);
void	sigint_handler(int sig);

// === LEXER Y PARSER ===
t_token	*tokenize_line(char *line);
int		is_special_char(char c);
t_cmd	*parse_tokens(t_shell *shell, t_token *tokens);
int		syntax_check(t_token *tokens);
t_token	*create_token(t_token_type type, char *value);
void	add_token(t_token **tokens, t_token_type type, char *value);
//void	add_redirection(t_redir **redirs, t_redir_type type, char *file);
void add_redirection(t_cmd *cmd, t_token *token);

void	add_to_argv(char ***argv, char *arg);

// === EXPANSIÓN ===
void	expand_variables(t_shell *shell, char **word);
void	expand_exit_status(t_shell *shell, char **result);
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

// === BUILTINS ===
int		builtin_echo(t_shell *shell, char **argv);
int		builtin_cd(t_shell *shell, char **argv);
int		builtin_pwd(t_shell *shell, char **argv);
int		builtin_export(t_shell *shell, char **argv);
int		builtin_unset(t_shell *shell, char **argv);
int		builtin_env(t_shell *shell, char **argv);
int		builtin_exit(t_shell *shell, char **argv);
int		is_valid_identifier(char *str);
int		is_valid_exit_arg(char *arg);

// === UTILS ===
void	error_msg(const char *msg);
void	error_exit(char *msg);
void	free_array(char **array);
void	free_cmd(t_cmd *cmd);
void	free_tokens(t_token *tokens);
void	free_redirs(t_redir *redirs);
char	*get_cmd_path(const char *cmd, char **envp);
char	*get_env_value(t_shell *shell, const char *name);
char	**copy_env(char **envp);
int		add_env_var(t_shell *shell, char *var);
int		remove_env_var(t_shell *shell, char *var);
void    set_env_var(t_shell *shell, const char *name, const char *value);
void free_cmd_list(t_cmd *head);

#endif
