/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnudes <nimatura@student.42barcel>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:16:07 by ohnudes           #+#    #+#             */
/*   Updated: 2024/08/18 20:09:00 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

char	*exit_mem(char **str)
{
	free(*str);
	*str = NULL;
	return (*str);
}

static char	*fetch_to_buffer(char *buffer, int fd, int *rbytes)
{
	char	*read_buffer;

	if (!aux_stralloc(&read_buffer, BUFFER_SIZE))
	{
		if (NULL != buffer)
			free(buffer);
		return (NULL);
	}
	while (NULL == aux_strchr(buffer, '\n'))
	{
		*rbytes = read(fd, read_buffer, BUFFER_SIZE);
		if (*rbytes == -1)
			break ;
		read_buffer[*rbytes] = '\0';
		buffer = aux_strjoin_p(buffer, read_buffer);
		if (*rbytes < BUFFER_SIZE)
			break ;
	}
	free(read_buffer);
	return (buffer);
}

static char	*trim_to_line(char *buffer)
{
	char	*line;
	char	*ref;
	size_t	i;

	line = NULL;
	i = 0;
	if (NULL != buffer && *buffer != '\0')
	{
		while (buffer[i] != '\0' && buffer[i] != '\n')
			i++;
		if (buffer[i] == '\n')
			i++;
		if (0 == aux_stralloc(&line, i))
			return (line);
		ref = line;
		while (i--)
			*(ref++) = *(buffer++);
	}
	return (line);
}

static char	*trim_to_buffer(char *buffer)
{
	char	*tmp;
	char	*match;

	if (NULL == buffer)
		return (NULL);
	match = aux_strchr(buffer, '\n');
	if (NULL == match || (match && *(match + 1) == '\0'))
	{
		free(buffer);
		buffer = NULL;
	}
	else
	{
		tmp = buffer;
		buffer = aux_strndup(++match);
		free(tmp);
	}
	if (NULL != buffer && *buffer == '\0')
	{
		free(buffer);
		buffer = NULL;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			rbytes;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	rbytes = 0;
	if (NULL == buffer || (buffer && NULL == aux_strchr(buffer, '\n')))
		buffer = fetch_to_buffer(buffer, fd, &rbytes);
	if (-1 == rbytes && NULL != buffer)
		return (exit_mem(&buffer));
	if (NULL != buffer)
	{
		line = trim_to_line(buffer);
		if (NULL == line)
			return (exit_mem(&buffer));
		buffer = trim_to_buffer(buffer);
	}
	return (line);
}
/*
#include <fcntl.h>
int	main(void)
{
	char	*str;
	int	fd;

	fd = open("txt", O_CREAT | O_RDWR, 0666);
	while (1)
	{
		str = get_next_line(fd);
		if (NULL == str)
			break ;
		write(1, str, aux_strlen_p(str));
		free(str);
	}
	close(fd);
	return (0);
}*/
