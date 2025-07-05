/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:04:01 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/10/08 13:10:43 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

int	ft_lstsize(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
/*
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
	
	ft_lstadd_front(&node, node1);
	ft_lstadd_front(&node, node2);
	ft_lstadd_front(&node, node3);
	ft_lstadd_front(&node, node4);

	printf("list size = %d\n", ft_lstsize(node));
}*/
