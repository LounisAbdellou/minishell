/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:23:41 by labdello          #+#    #+#             */
/*   Updated: 2024/08/03 19:08:02 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BUFFER_SIZE 5

size_t	find_index(char *str, char needle)
{
	size_t	i;

	i = 0;
	while (i + 1)
	{
		if (str[i] == needle)
			return (i);
		else if (str[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

static char	*get_line(int fd, char *rest, char *buffer)
{
	char		*tmp;
	ssize_t		read_len;

	read_len = 1;
	while (read_len)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == -1)
		{
			free(rest);
			return (NULL);
		}
		if (read_len == 0)
			break ;
		buffer[read_len] = '\0';
		if (!rest)
			rest = ft_strndup("", 0);
		tmp = rest;
		rest = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (find_index(buffer, '\n'))
			break ;
	}
	return (rest);
}

static char	*trim_line(char *line)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	len = ft_strlen(line);
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[i + 1] == 0)
		return (NULL);
	i += 1;
	str = ft_strndup(line + i, len - i);
	if (*str == '\0')
	{
		free(str);
		str = NULL;
	}
	line[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		buffer[BUFFER_SIZE];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	line = get_line(fd, rest, buffer);
	if (!line)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	rest = trim_line(line);
	return (line);
}
