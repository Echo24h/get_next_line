/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:50:47 by gborne            #+#    #+#             */
/*   Updated: 2022/01/12 00:44:09 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*line;
	static char		*mem = NULL;
	char			buff[BUFFER_SIZE + 1];

	line = NULL;
	if (fd < 0 || read(fd, buff, 0) < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff[read(fd, buff, BUFFER_SIZE)] = '\0';
	mem = s_ljoin(mem, buff, s_len(mem), s_len(buff));
	while (s_len(buff) && !(s_chr(buff, '\n', 0)))
	{
		buff[read(fd, buff, BUFFER_SIZE)] = '\0';
		mem = s_ljoin(mem, buff, s_len(mem), s_len(buff));
	}
	if (mem)
	{
		line = treat_line(mem, line);
		mem = treat_mem(mem);
	}
	return (line);
}

char	*treat_mem(char *mem)
{
	char			*new;
	unsigned long	len;

	new = NULL;
	len = s_len(s_chr(mem, '\n', 1));
	if (len)
	{
		new = (char *)malloc(sizeof(char) * len + 1);
		s_lcpy(new, s_chr(mem, '\n', 1), len + 1);
	}
	free(mem);
	return (new);
}

char	*treat_line(char *mem, char *line)
{
	unsigned long	len;

	line = NULL;
	len = s_len(mem) - s_len(s_chr(mem, '\n', 1));
	if (len)
	{
		line = (char *)malloc(sizeof(char) * len + 1);
		s_lcpy(line, mem, len + 1);
	}
	return (line);
}
