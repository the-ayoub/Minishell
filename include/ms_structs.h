/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 23:05:39 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/29 20:06:37 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H
# include "../libft/inc/libft.h"
// What the fuck is this
# include <termios.h>

// Estados para el análisis de comillas
typedef enum e_parse_state
{
	STATE_GENERAL,
	STATE_IN_SQUOTE,
	STATE_IN_DQUOTE
}	t_parse_state;

// === TIPOS DE TOKENS ===
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_WORD_SQ,
	TOKEN_WORD_DQ,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

// === ESTRUCTURA DE UN TOKEN ===
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	int				link;
}	t_token;

// === TIPOS DE REDIRECCIÓN ===
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_redir_type;

// === ESTRUCTURA DE REDIRECCIÓN ===
typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

// === ESTRUCTURA DE UN COMANDO ===
typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

// === ESTRUCTURA DEL SHELL ===
typedef struct s_shell
{
	struct termios	orig_termios;
	t_list			*raw_env;
	char			**env;
	int				last_status;
	t_token			*tokens;
	t_cmd			*cmd;
	int				interactive;
	int				in_input_phase;
}	t_shell;

typedef struct s_pipe
{
	int				pipe_fd[2];
	int				b_std[2];
	pid_t			last_pid;
	int				prev_read_end;
	pid_t			pid;
}					t_pipe;

typedef struct s_expans
{
	char			*to_expand;
	char			*matching_env;
	char			*token_str;
	char			*var_name;
	int				false_env;
}					t_expand;

typedef struct s_paths
{
	char			*env;
	char			*cpy;
	char			*full;
	char			**paths;
	int				i;
}		t_paths;
#endif
