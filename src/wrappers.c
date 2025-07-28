/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 23:03:22 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/28 19:27:15 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wrapper_free_lst(t_list *head)
{
	t_list	*ptr;
	t_list	*fwd;

	if (head == NULL)
		return ;
	ptr = head;
	while (ptr != NULL)
	{
		fwd = ptr->next;
		free(ptr->content);
		ptr->content = NULL;
		free(ptr);
		ptr = fwd;
	}
	head = NULL;
}

int	wrapper_strjoin(char **s1, char *s2)
{
	char	*tmp;

	if (s1 && *s1 && s2)
	{
		tmp = ft_strjoin(*s1, s2);
		if (NULL == tmp)
			return (FALSE);
		free(*s1);
		*s1 = tmp;
		return (TRUE);
	}
	if (s1 == NULL || *s1 == NULL)
		if (s2 != NULL)
			*s1 = ft_strdup(s2);
	return (FALSE);
}

int	wrapper_dup2(int oldfd, int newfd, t_shell *shell)
{
	if (dup2(oldfd, newfd) == -1)
	{
		shell->last_status = 2;
		return (FALSE);
	}
	return (TRUE);
}

int	wrapper_dup(int *holder, int fd, t_shell *shell)
{
	*holder = dup(fd);
	if (*holder == -1)
	{
		shell->last_status = 2;
		return (FALSE);
	}
	return (TRUE);
}

t_token	*wrapper_exit(t_token **head)
{
	free_tokens(*head);
	*head = NULL;
	return (NULL);
}
