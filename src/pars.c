/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:42:45 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/07 20:10:32 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	expand_dollar(t_shell *shell, char **result, char *ptr)
{
	int		len;
	char	*var_name;
	char	*var_value;
	char	*start_ptr;
	char	*new;

	len = 1;
	var_name = NULL;
	var_value = NULL;
	start_ptr = ptr;
	if (ptr[1] == '?') // Manejo de $?
	{
		var_value = ft_itoa(shell->last_status);
		len = 2;
	}
	else if (ft_isalnum(ptr[1]) || ptr[1] == '_')
	{
		start_ptr = ptr + 1;
		ptr = start_ptr;
		while (ft_isalnum(*ptr) || *ptr == '_')
			ptr++;
		len = ptr - start_ptr;
		var_name = ft_substr(start_ptr, 0, len);
		var_value = get_env_value(shell, var_name);
		len++;
	}
	else
	{
		append_char(result, '$');
		return (1);
	}
	if (var_value)
	{
		new = ft_strjoin(*result, var_value);
		free(*result);
		*result = new;
		free(var_value);
	}
	if (var_name)
		free(var_name);
	return (len);
}

void	append_char(char **str, char c)
{
	char	*new_str;
	int		len;

	len = *str ? ft_strlen(*str) : 0;
	new_str = malloc(len + 2);
	if (!new_str)
		return ;
	if (*str)
		ft_memcpy(new_str, *str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	if (*str)
		free(*str);
	*str = new_str;
}

int	syntax_check(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (1);
	if (tokens->type == TOKEN_PIPE)
		return (1);
	current = tokens;
	while (current)
	{
		if (current->type >= TOKEN_REDIR_IN && current->type <= TOKEN_HEREDOC)
		{
			if (!current->next || current->next->type != TOKEN_WORD)
				return (1);
			current = current->next;
		}
		else if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type == TOKEN_PIPE)
				return (1);
		}
		current = current->next;
	}
	return (0);
}

static void	add_argument(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_argv;

	count = 0;
	if (cmd->argv)
	{
		while (cmd->argv[count])
			count++;
	}
	new_argv = malloc((count + 2) * sizeof(char *));
	if (!new_argv)
		return ;
	for (int i = 0; i < count; i++)
	{
		new_argv[i] = cmd->argv[i];
	}
	new_argv[count] = arg;
	new_argv[count + 1] = NULL;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = new_argv;
}

static t_redir	*create_redirection(t_redir_type type, char *file)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = file;
	new->next = NULL;
	return (new);
}
void	add_redirection(t_cmd *cmd, t_token *token)
{
	t_redir_type	type;
	char			*file;
	t_redir			*new_redir;
	t_redir			*last;

	file = NULL;
	if (token->type == TOKEN_REDIR_IN)
		type = REDIR_IN;
	else if (token->type == TOKEN_REDIR_OUT)
		type = REDIR_OUT;
	else if (token->type == TOKEN_REDIR_APPEND)
		type = REDIR_APPEND;
	else if (token->type == TOKEN_HEREDOC)
		type = REDIR_HEREDOC;
	else
		return ;
	if (token->next && token->next->type == TOKEN_WORD)
	{
		file = ft_strdup(token->next->value);
	}
	if (!file)
		return ;
	new_redir = create_redirection(type, file);
	if (!new_redir)
	{
		free(file);
		return ;
	}
	if (!cmd->redirs)
	{
		cmd->redirs = new_redir;
	}
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

static t_cmd	*create_new_command(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argv = NULL;
	new->redirs = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*parse_tokens(t_shell *shell, t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current_cmd;
	t_token	*current;

	(void)shell;
	head = NULL;
	current_cmd = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!current_cmd)
			{
				ft_putstr_fd("minishell: syntax error near `|'\n",
					STDERR_FILENO);
				free_cmd_list(head);
				return (NULL);
			}
			current_cmd->next = create_new_command();
			current_cmd = current_cmd->next;
			current = current->next;
			continue ;
		}
		if (!current_cmd)
		{
			current_cmd = create_new_command();
			head = current_cmd;
		}
		if (current->type == TOKEN_WORD)
			add_argument(current_cmd, ft_strdup(current->value));
		else if (current->type >= TOKEN_REDIR_IN
			&& current->type <= TOKEN_HEREDOC)
		{
			if (!current->next || current->next->type != TOKEN_WORD)
			{
				ft_putstr_fd("minishell: syntax error near redirection\n",
					STDERR_FILENO);
				free_cmd_list(head);
				return (NULL);
			}
			add_redirection(current_cmd, current);
			current = current->next;
		}
		else
		{
			ft_putstr_fd("minishell: unknown token type\n", STDERR_FILENO);
			free_cmd_list(head);
			return (NULL);
		}
		current = current->next;
	}
	return (head);
}
