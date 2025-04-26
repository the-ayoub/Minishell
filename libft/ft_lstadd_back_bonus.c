/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:55:02 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/10/08 13:30:37 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
/*
#include <stdio.h>
int main (void)
{
	t_list *node;
	t_list *node1;
	t_list *node2;
	t_list *node3;
	t_list *node4;

	node = ft_lstnew("3 nodo");
	node1 = ft_lstnew("2 nodo");
	node2 = ft_lstnew("1 nodo");
	node3 = ft_lstnew("1 nodo");
	node4 = ft_lstnew("1 nodo");
	
	ft_lstadd_back(&node, node1);
	ft_lstadd_back(&node, node2);
	ft_lstadd_back(&node, node3);
	ft_lstadd_back(&node, node4);

	printf("list size = %d\n", ft_lstsize(node));
}*/
