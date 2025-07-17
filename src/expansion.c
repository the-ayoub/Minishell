/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:39:44 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/17 13:33:14 by ohnonon          ###   ########.fr       */
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

char	*locate_env_var(t_list *data, char *str)
{
	t_list	*iter;
	char	*var_name;

	iter = data;
	while (iter != NULL)
	{
		var_name = ft_strtrim(iter->content, "=");
		if (var_name == NULL)
		{
			iter = iter->next;
			continue ;
		}
		if (ft_strncmp(str, var_name, ft_strlen(var_name)) == 0)
		{
			free(var_name);
			break ;
		}
		iter = iter->next;
	}
	if (NULL == iter)
		return (NULL);
	return (iter->content);
}

char	*get_var_name(char *str)
{
	char	*var_name;
	size_t	i;

	i = 0;
	var_name = NULL;
	if (str == NULL)
		return (NULL);
	if (str[i] && str[i] == '$')
		i++;
	if (str[i] && ft_isspace(str[i]))
		return (NULL);
	if (str[i])
		str = &str[i];
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		str[i] = '\0';
	var_name = ft_strdup(str);
	str[i] = '\n';
	return (var_name);
}

// if it finds a match but isnt a valid variable it will return the old str
char	*find_and_expand_var(t_shell *shell, char *old)
{
	char	*var;
	char	*var_value;

	var = get_var_name(ft_strchr(old, '$'));
	if (NULL == var) // var not valid syntax
		return (old);
	var_value = locate_env_var()

	return (new);
}

// expand var and strjoin with prev and after unless space or another var
// or tab
int	expand_variables(t_shell *shell, t_token *head)
{
	t_token	*iter;
	
	(void)shell;
	iter = head;
	while (NULL != iter)
	{
		if (iter->type != TOKEN_WORD && iter->type != TOKEN_WORD_DQ)
		{
			iter = iter->next;
			continue;
		}
		if (ft_strchr(iter->value, '$') == NULL)
			continue ;
		iter->value = find_and_expand_var(shell, iter->value);
		if (iter->va
	}
	return (0);
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
