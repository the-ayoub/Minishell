/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 23:56:49 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/10 19:52:29 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**expand_env_var(char *var)
{
	char	**expanded_var;
	int		i;

	i = 0;
	expanded_var = NULL;
	while (var[i] != '=')
	{
		while (var[i] != '\0' && ft_isspace(var[i]))
			i++;
		while (var[i] != '\0' && ft_isalpha(var[i]))
			i++;
		while (var[i] != '\0' && (ft_isalnum(var[i]) || var[i] == '_'))
			i++;
	}
	if (var[i] == '=')
		i++;
	if (var[i] != '\0')
		expanded_var = ft_split(&var[i], ':');
	return (expanded_var);
}

void	print_arr(char **str)
{
	while (str != NULL && *str != NULL)
		printf("	%s\n", *(str++));
}

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

static void	free_split_wrp(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != NULL)
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
	}
	free(str);
	str = NULL;
}

void	expand_arr_and_print(t_list *lst)
{
	t_list	*iter;
	char	**expanded_variable;

	iter = lst;
	while (iter != NULL)
	{
		expanded_variable = expand_env_var(iter->content);
		printf("EXPANDING	>>	%s\n\n", (char *)iter->content);
		print_arr(expanded_variable);
		printf("%p\n", iter);
		printf("\n\n");
		free_split_wrp(expanded_variable);
		iter = iter->next;
	}
}
