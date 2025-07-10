/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnudes <nimatura@student.42barcel>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:54:14 by ohnudes           #+#    #+#             */
/*   Updated: 2024/12/24 16:17:47 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

char	*exit_mem(char **str);
size_t	aux_strlen_p(char *str);
char	*aux_strndup(char *src);
char	*aux_strchr(char *str, int set);
int		aux_stralloc(char **str, size_t size);
char	*aux_strjoin_p(char *dst, char *concat);

#endif
