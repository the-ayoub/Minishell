/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:56:20 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/16 21:10:41 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_argument(t_cmd *cmd, char *arg)
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

t_redir	*create_redirection(t_redir_type type, char *file)
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

t_cmd	*create_new_command(void)
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

// returns 1 in success, 0 for err
int	parse_pipe(t_token **current, t_cmd **cmd, t_cmd **ptr)
{
	if (NULL == *cmd)
	{
		ft_putstr_fd("minishell: syntax error near `|'\n",
			   STDERR_FILENO);
		free_cmd_list(*ptr);
		return (0);
	}
	(*cmd)->next = create_new_command();
	*cmd = (*cmd)->next;
	*current = (*current)->next;
	return (1);
}
