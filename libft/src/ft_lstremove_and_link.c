/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_and_link.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:54:31 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/11 20:37:01 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

// Removes a [node] from the [head] lst. If the node is not found, the function
// will not do anything
void	ft_lstremove_and_link(t_list **head, t_list *node)
{
	t_list *tmp;
	t_list *next;

	if (*head == NULL || node == NULL)
		return ;
	if (*head == node)
	{
		tmp = (*head)->next;
		ft_lstdelone(*head, &free);
		*head = tmp;
	}
	else
	{
		tmp = *head;
		while (tmp->next != NULL && tmp->next != node)
			tmp = tmp->next;
		if (tmp->next != node)
			return ;
		next = (tmp->next)->next;
		ft_lstdelone(tmp->next, &free);
		tmp->next = next;
	}
}
