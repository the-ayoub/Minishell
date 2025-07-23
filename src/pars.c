/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:42:45 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/23 23:18:44 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_token_word(t_token_type type)
{
	return (type == TOKEN_WORD || type == TOKEN_WORD_DQ \
	|| type == TOKEN_WORD_SQ);
}

static int	aux_add_redir(t_token *token, t_redir_type *type, char **file)
{
	*file = NULL;
	if (token->type == TOKEN_REDIR_IN)
		*type = REDIR_IN;
	else if (token->type == TOKEN_REDIR_OUT)
		*type = REDIR_OUT;
	else if (token->type == TOKEN_REDIR_APPEND)
		*type = REDIR_APPEND;
	else if (token->type == TOKEN_HEREDOC)
		*type = REDIR_HEREDOC;
	else
		return (0);
	if (token->next && is_token_word(token->next->type))
		*file = ft_strdup(token->next->value);
	if (NULL == *file)
		return (0);
	return (1);
}

// WARNING: no filename token
static void	add_redirection(t_cmd *cmd, t_token *token)
{
	t_redir_type	type;
	char			*file;
	t_redir			*new_redir;
	t_redir			*last;

	if (aux_add_redir(token, &type, &file) == 0)
		return ;
	new_redir = create_redirection(type, file);
	if (!new_redir)
	{
		free(file);
		return ;
	}
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

// returns 1 in success, 0 for err
static int	parse_redir(t_token **current, t_cmd **cmd, t_cmd **ptr)
{
	if (NULL == (*current)->next || !is_token_word((*current)->next->type))
	{
		ft_putstr_fd("minishell: syntax error near redirection\n",
			   STDERR_FILENO);
		free_cmd_list(*ptr);
		return (0);
	}
	add_redirection(*cmd, *current);
	*current = (*current)->next;
	return (1);
}

// RETURNS 0 in case of success
int	parse_tokens(t_shell *shell, t_token *tokens, t_cmd **ptr)
{
	t_cmd	*head;
	t_cmd	*current_cmd;
	t_token	*current;

	(void)shell;
	current_cmd = NULL;
	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (parse_pipe(&current, &current_cmd, ptr) == 0)
				return (1);
			continue ;
		}
		if (NULL == current_cmd)
		{
			current_cmd = create_new_command();
			head = current_cmd;
		}
		if (is_token_word(current->type))
			add_argument(current_cmd, ft_strdup(current->value));
		else if (current->type >= TOKEN_REDIR_IN \
				&& current->type <= TOKEN_HEREDOC)
			parse_redir(&current, &current_cmd, ptr);
		current = current->next;
	}
	*ptr = head;
	return (0);
}
