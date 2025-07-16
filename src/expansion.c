/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:39:44 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/16 21:53:19 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_exit_status(t_shell *shell, char **result)
{
	char	*exit_str;
	char	*new_result;

	exit_str = ft_itoa(shell->last_status);
	new_result = ft_strjoin(*result, exit_str);
	free(*result);
	free(exit_str);
	*result = new_result;
}

// NOTE: Tokens aren't needed at this step
void	expand_variables(t_shell *shell, t_cmd *head)
{
	t_cmd	*iter;
	char	**i_str;
	
	iter = head;
	while (NULL != iter)
	{
		i_str = head->argv;
		while (NULL != i_str)
		{


		}
	}
}
	// char	*result;
	// char	*ptr = NULL;
	// int		in_squote;
	// int		in_dquote;
	// char	str[2] = {*ptr, '\0'};
	// char	*new_temp;
	//
	// ptr = NULL;
	// ptr = NULL;
	// result = ft_strdup("");
	// ptr = *word;
	// in_squote = 0;
	// in_dquote = 0;
	// while (*ptr)
	// {
	// 	if (*ptr == '\'' && !in_dquote)
	// 		in_squote = !in_squote;
	// 	else if (*ptr == '"' && !in_squote)
	// 		in_dquote = !in_dquote;
	// 	else if (*ptr == '$' && !in_squote)
	// 	{
	// 		if (ptr[1] == '?')
	// 		{
	// 			expand_exit_status(shell, &result);
	// 			ptr += 2;
	// 			continue ;
	// 		}
	// 	}
	// 	new_temp = ft_strjoin(result, str);
	// 	free(result);
	// 	result = new_temp;
	// 	ptr++;
	// }
	// free(*word);
	// *word = result;
