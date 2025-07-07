/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:39:44 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/07 20:23:40 by aybelhaj         ###   ########.fr       */
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

void	expand_variables(t_shell *shell, char **word)
{
	char	*result;
	char	*ptr = NULL;
	int		in_squote;
	int		in_dquote;
	char	str[2] = {*ptr, '\0'};
	char	*new_temp;

	ptr = NULL;
	ptr = NULL;
	result = ft_strdup("");
	ptr = *word;
	in_squote = 0;
	in_dquote = 0;
	while (*ptr)
	{
		if (*ptr == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (*ptr == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (*ptr == '$' && !in_squote)
		{
			if (ptr[1] == '?')
			{
				expand_exit_status(shell, &result);
				ptr += 2;
				continue ;
			}
		}
		new_temp = ft_strjoin(result, str);
		free(result);
		result = new_temp;
		ptr++;
	}
	free(*word);
	*word = result;
}
