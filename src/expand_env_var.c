/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:39:22 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/16 20:39:48 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	expand_dollar(t_shell *shell, char **result, char *ptr)
{
	int		len;
	char	*var_name;
	char	*var_value;
	char	*start_ptr;
	char	*new;

	len = 1;
	var_name = NULL;
	var_value = NULL;
	start_ptr = ptr;
	if (ptr[1] == '?') // Manejo de $?
	{
		var_value = ft_itoa(shell->last_status);
		len = 2;
	}
	else if (ft_isalnum(ptr[1]) || ptr[1] == '_')
	{
		start_ptr = ptr + 1;
		ptr = start_ptr;
		while (ft_isalnum(*ptr) || *ptr == '_')
			ptr++;
		len = ptr - start_ptr;
		var_name = ft_substr(start_ptr, 0, len);
		var_value = get_env_value(shell, var_name);
		len++;
	}
	else
	{
		append_char(result, '$');
		return (1);
	}
	if (var_value)
	{
		new = ft_strjoin(*result, var_value);
		free(*result);
		*result = new;
		free(var_value);
	}
	if (var_name)
		free(var_name);
	return (len);
}

void	append_char(char **str, char c)
{
	char	*new_str;
	int		len;

	len = *str ? ft_strlen(*str) : 0;
	new_str = malloc(len + 2);
	if (!new_str)
		return ;
	if (*str)
		ft_memcpy(new_str, *str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	if (*str)
		free(*str);
	*str = new_str;
}

