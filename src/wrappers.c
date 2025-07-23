/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 23:03:22 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/23 23:07:29 by nimatura         ###   ########.fr       */
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

	if (s1 == NULL || *s1 == NULL || s2 == NULL)
		return (FALSE);
	tmp = ft_strjoin(*s1, s2);
	if (NULL == tmp)
		return (FALSE);
	free(*s1);
	*s1 = tmp;
	return (TRUE);
}

int	wrapper_dup2(int oldfd, int newfd, t_shell *shell)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2 failed");
		shell->last_status = 1;
		return (FALSE);
	}
	return (TRUE);
}

int	wrapper_dup(int *holder, int fd, t_shell *shell)
{
	*holder = dup(fd);
	if (*holder == -1)
	{
		perror("dup failed");
		shell->last_status = 1;
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
