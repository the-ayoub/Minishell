/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_and_link.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:54:31 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/11 18:58:04 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstremove_and_link(t_list **head, t_list *node)
{
	t_list *tmp;
	t_list *next;

	if (*head == NULL)
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

	}
}
