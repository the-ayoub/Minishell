/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 22:39:49 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/30 18:26:27 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_expand(t_expand *dt)
{
	dt->token_str = NULL;
	dt->to_expand = NULL;
	dt->matching_env = NULL;
	dt->var_name = NULL;
	dt->false_env = 0;
}

int	aux_upd_data(t_expand *dt, char *match, char *var_name, char *env_var)
{
	dt->matching_env = env_var;
	dt->to_expand = match;
	dt->var_name = var_name;
	return (1);
}
