/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnudes </var/spool/mail/ohnudes>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:50:09 by ohnudes           #+#    #+#             */
/*   Updated: 2024/08/18 20:12:12 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

typedef struct s_data
{
	int	errctl;
	int	lenght;
}				t_data;

void	aux_printc(const char c, t_data *data);
void	aux_printstr(const char *str, t_data *data);

void	convert_nbr(int nbr, t_data *data);
void	convert_nbrbase(unsigned long nbr, char *base, int blen, t_data *data);
void	convert_ptrtoint(void *ptr, t_data *data);

void	parse_format(char format, t_data *data, va_list args);
int		ft_printf(const char *str, ...);

#endif
