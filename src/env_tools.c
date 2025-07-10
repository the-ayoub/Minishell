/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:49:11 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/10 21:10:07 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_env_var(t_minishell *data, char *buffer)
{
	t_list	*new_var;
	char	*var_str;
	
	if (*buffer == '\0')
		return ;
	if (!is_var_name_ok(buffer))
	{
		//print err msg
		return ;
	}
	while (*buffer != '\0' && ft_isspace(*buffer))
		buffer++;
	var_str = ft_strdup_env(buffer);
	if (var_str != NULL)
	{
		new_var = ft_lstnew(var_str);
		ft_lstadd_back(&data->env_lst, new_var);
	}
}

// WARNING: MALLOC
char	**expand_env_var(char *var)
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

// Returns the node in which its content matches with the str.
// char	*locate_env_var(t_minishell *data, char *str)
// {
// 	t_list	*iter;
//
// 	iter = data->env_lst;
// 	while (iter != NULL)
// 	{
// 		if (ft_strncmp(str, iter->content, ft_strlen(str)) == 0)
// 			break ;
// 		iter = iter->next;
// 	}
// 	if (NULL == iter)
// 		return (NULL);
// 	return (iter->content);
// }

// WARNING: MALLOC
// Isolates the var name without the '=' sign and returns an allocated str
// with the name
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

// WARNING: in subft: MALLOC
//		substracts the var name delimited by $ and = and then iterates the list
// looking for a match. Prints the trimmed lst->content;
//
// TODO: Printing str, in case of not being a var_name, means that it needs to
// print everything, decide how to handle
//
// NOTE: At some point this function will need to return something for the case
// that it doesn't find a match with the var name
void search_and_print_env_var(t_minishell *data, char *str)
{
	char	*var_name;
	char	*match;
	size_t	len;

	if (NULL == str)
		return ;
	// return (NULL);
	while (str && ft_isspace(*str))
		str++;
	var_name = get_var_name(str);
	if (NULL == var_name)
	{
		printf("%s", str);
		return ;
	}
	match = locate_env_var(data, var_name);
	if (match != NULL)
	{
		len = ft_strlen(var_name);
		printf("%s\n", match + len + 1);
	}
	free(var_name);
}

/* NOTES
 * Hay 3 filtros antes de aceptar la request de expansion de variable!
*	- Si no cumple para ser candidato a expandir, 
*	(porque empieza por num o caracter especial)
*	lo mostraremos por pantalla hasta el ‘\0’ o hasta un ‘$’ 
*	donde volveremos a evaluar si es expandible.
*/

size_t	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	while (str[i] != '\0' && ft_isalpha(str[i]))
		i++;
	while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] != '\0' && str[i] == '=')
		i++;
	else
		return (0);
	if (str[i] != '"' || str[i] != '\'')
	{
		while (str[i] != '\0' && (!ft_isspace(str[i]) && ft_isprint(str[i] == '_')))
			i++;
	}
	return (i);
}

int	is_var_name_ok(char *str)
{
	int	i;

	i = 6;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	while (str[i] != '\0' && ft_isalpha(str[i]))
		i++;
	while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

char	*ft_strdup_env(const char *src)
{
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	len = get_var_len((char *)src);
	str = ft_calloc(len + 1, 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}

