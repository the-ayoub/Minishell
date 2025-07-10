/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnudes </var/spool/mail/ohnudes>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:11:54 by ohnudes           #+#    #+#             */
/*   Updated: 2024/08/18 20:09:55 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	aux_printc(const char c, t_data *data)
{
	if (data->errctl == -1)
		return ;
	data->errctl = write(1, &c, 1);
	if (data->errctl == 1)
		data->lenght++;
}

void	aux_printstr(const char *str, t_data *data)
{
	if (str == NULL)
		aux_printstr("(null)", data);
	else
	{
		if (data->errctl == -1)
			return ;
		while (*str && data->errctl >= 0)
		{
			data->errctl = write(1, str++, 1);
			if (data->errctl == 1)
				data->lenght++;
		}
	}
}

void	parse_format(char format, t_data *dt, va_list args)
{
	if (dt->errctl == -1)
		return ;
	if (format == 'c')
		aux_printc(va_arg(args, int), dt);
	else if (format == 's')
		aux_printstr(va_arg(args, char *), dt);
	else if (format == 'i' || format == 'd')
		convert_nbr(va_arg(args, int), dt);
	else if (format == 'u')
		convert_nbrbase(va_arg(args, unsigned int), "0123456789", 10, dt);
	else if (format == 'x')
		convert_nbrbase(va_arg(args, unsigned int), "0123456789abcdef", 16, dt);
	else if (format == 'X')
		convert_nbrbase(va_arg(args, unsigned int), "0123456789ABCDEF", 16, dt);
	else if (format == 'p')
		convert_ptrtoint(va_arg(args, void *), dt);
	else if (format == '%')
		aux_printc('%', dt);
	else
		dt->errctl = -1;
}
