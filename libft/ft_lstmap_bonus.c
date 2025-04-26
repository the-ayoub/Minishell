/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:59:07 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/10/13 17:58:06 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//void *mod(void *lst);
//void *lib(void *lst);

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst != NULL)
	{
		new_node = ft_lstnew(f(lst->content));
		if (new_node == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
void *mod(t_list *lst)
{
	t_list	*lst_local;

	lst_local = (t_list *)lst;
	if(!lst_local)
		return (NULL);
	lst_local->content = "hola";
	return (lst_local);
}

void lib(t_list *lst)
{
	t_list *temp;
	t_list lst_local;

	lst_local = lst;
        if(!lst_local)
                return (NULL);
        while (*lst_local)
        {
                temp = *lst_local->next;
                free (*lst_local);
                *lst_local = temp;
	}
}

void main (void)
{
	void *(*f)(void*) = &mod;
	void *(del)(void*) = &lib;
	t_list *node;
        t_list *node1;
        t_list *node2;
        t_list *node3;
        node = ft_lstnew("3 nodo");
        node1 = ft_lstnew("2 nodo");
        node2 = ft_lstnew("1 nodo");
        node3 = ft_lstnew("1 nodo");
        ft_lstadd_back(&node, node1);
        ft_lstadd_back(&node, node2);
        ft_lstadd_back(&node, node3);
	ft_lstmap(node, f , del);
	return (0);
}*/
