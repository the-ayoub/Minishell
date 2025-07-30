/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 23:56:49 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/30 18:29:51 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_lst(t_list *ptr)
{
	t_list	*iter;

	iter = ptr;
	while (iter != NULL)
	{
		printf("%s\n", (char *)iter->content);
		iter = iter->next;
	}
}
