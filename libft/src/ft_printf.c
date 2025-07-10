/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnudes </var/spool/mail/ohnudes>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:53:18 by ohnudes           #+#    #+#             */
/*   Updated: 2024/08/18 20:10:15 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static t_data	init_data(t_data data)
{
	data.errctl = 0;
	data.lenght = 0;
	return (data);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_data	data;
	int		i;

	i = 0;
	data = init_data(data);
	va_start(args, str);
	while (str[i] != '\0' && data.errctl != -1)
	{
		if (str[i] != '%')
			aux_printc(str[i++], &data);
		else if (str[i] == '%')
		{
			parse_format(str[++i], &data, args);
			i++;
		}
		if (data.errctl == -1)
			return (data.errctl);
	}
	va_end(args);
	return (data.lenght);
}
