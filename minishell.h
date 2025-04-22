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
    TOKEN_WORD,        // palabra (comando o argumento)
    TOKEN_PIPE,        // |
    TOKEN_REDIR_IN,    // 
    TOKEN_REDIR_OUT,   // >
    TOKEN_REDIR_APPEND, // >>
    TOKEN_HEREDOC,     // 
    TOKEN_AND,         // && (bonus)
    TOKEN_OR,          // || (bonus)
    TOKEN_OPEN_PAR,    // ( (bonus)
    TOKEN_CLOSE_PAR,   // ) (bonus)
}   t_token_type;

// === ESTRUCTURA DE UN TOKEN ===
typedef struct s_token
{
    t_token_type    type;
    char            *value;
    struct s_token  *next;
}   t_token;

// === TIPOS DE REDIRECCIÓN ===
typedef enum e_redir_type
{
    REDIR_IN,       // 
    REDIR_OUT,      // >
    REDIR_APPEND,   // >>
    REDIR_HEREDOC   // 
}   t_redir_type;

// === ESTRUCTURA DE REDIRECCIÓN ===
typedef struct s_redir
{
    t_redir_type     type;
    char             *file;     // nombre del archivo o delimitador
    struct s_redir   *next;
}   t_redir;

// === ESTRUCTURA DE UN PROCESO ===
typedef struct s_process
{
    struct s_process    *next;
    char                **argv;       // argumentos del comando
    t_redir             *redirs;      // lista de redirecciones
    pid_t               pid;          // PID del proceso
    int                 completed;    // 1 si ha terminado
    int                 stopped;      // 1 si ha sido detenido
    int                 status;       // valor de retorno
    int                 pipe_in[2];   // pipe para entrada
    int                 pipe_out[2];  // pipe para salida
}   t_process;

// === ESTRUCTURA DE UN JOB ===
typedef struct s_job
{
    struct s_job    *next;
    char            *command;        // línea de comando completa (para logs)
    t_process       *first_process;  // lista enlazada de procesos
    pid_t           pgid;            // grupo de procesos
    int             notified;        // 1 si el usuario fue notificado del stop
    struct termios  tmodes;          // modos del terminal guardados
    int             stdin;
    int             stdout;
    int             stderr;
    int             operator;        // 0: nada, 1: &&, 2: || (bonus)
}   t_job;

// === ESTRUCTURA DEL SHELL ===
typedef struct s_shell
{
    t_job           *jobs;            // lista de jobs activos
    char            **env;            // copia del entorno
    struct termios  orig_termios;     // configuración original del terminal
    int             last_status;      // estado de salida del último comando
    t_token         *tokens;          // tokens de la línea de comando actual
    int             interactive;      // 1 si el shell es interactivo
}   t_shell;

// === VARIABLES GLOBALES ===
extern int g_signal_received;         // para manejar señales

// === FUNCIONES DE SHELL ===
void    init_shell(t_shell *shell, char **envp);
void    reset_terminal(t_shell *shell);
int     main_loop(t_shell *shell);

// === JOB CONTROL ===
void    add_job(t_shell *shell, t_job *job);
t_job   *find_job(t_shell *shell, pid_t pgid);
int     job_is_completed(t_job *job);
int     job_is_stopped(t_job *job);
void    wait_for_job(t_shell *shell, t_job *job);
void    update_job_status(t_shell *shell);

// === SIGNAL HANDLING ===
void    setup_signal_handlers(void);
void    ignore_signals(void);
void    default_signals(void);

// === LEXER Y PARSER ===
t_token *tokenize_line(char *line);
t_job   *parse_tokens(t_shell *shell, t_token *tokens);
void    expand_variables(t_shell *shell, char **word);
char    *expand_wildcards(char *pattern);  // bonus

// === EXECUCIÓN ===
void    execute_job(t_shell *shell, t_job *job);
int     is_builtin(char *cmd);
int     exec_builtin(t_shell *shell, t_process *process);
void    handle_redirections(t_process *process);

// === BUILTINS ===
int     builtin_echo(t_shell *shell, char **argv);
int     builtin_cd(t_shell *shell, char **argv);
int     builtin_pwd(t_shell *shell, char **argv);
int     builtin_export(t_shell *shell, char **argv);
int     builtin_unset(t_shell *shell, char **argv);
int     builtin_env(t_shell *shell, char **argv);
int     builtin_exit(t_shell *shell, char **argv);

// === UTILS ===
void    error_exit(const char *msg);
void    free_job(t_job *job);
void    free_tokens(t_token *tokens);
char    *get_cmd_path(const char *cmd, char **envp);
char    *get_env_value(t_shell *shell, const char *name);
void    print_jobs(t_shell *shell);

#endif
