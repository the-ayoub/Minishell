/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:05:33 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/10 19:52:52 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	print_lst(t_list *ptr)
// {
// 	t_list	*iter;
//
// 	iter = ptr;
// 	while (iter != NULL)
// 	{
// 		printf("%s\n", (char *)iter->content);
// 		iter = iter->next;
// 	}
// }

void	free_lst_wrp(t_list *head)
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
