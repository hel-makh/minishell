/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:17:07 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/29 11:36:35 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	end_check(char *dest)
{
	if (ft_strlen(dest) == 0)
	{
		free(dest);
		return (1);
	}
	return (0);
}

char	*ft_remove_old_line(char *line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*(line + i) != '\n' && *(line + i) != '\0')
		i = i + 1;
	if (*(line + i) == '\0')
	{
		free(line);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!str)
		return (NULL);
	i++;
	while (line[i] != '\0')
		str[j++] = line[i++];
	*(str + j) = '\0';
	free(line);
	if (end_check(str))
		return (NULL);
	return (str);
}

char	*ft_read_line(char *line, int fd)
{
	int		ret;
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	ret = 1;
	while (ret > 0 && ft_strchr(line, '\n') == NULL )
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			return (NULL);
		}
		if (ret == 0)
			break ;
		*(buff + ret) = '\0';
		line = ft_strjoin(line, buff);
	}
	free(buff);
	return (line);
}

char	*ft_first_line(char *line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*(line + i) != '\n' && *(line + i) != '\0')
	{
		i = i + 1;
	}
	if (*(line + i) == '\n')
	{
		i = i + 1;
	}
	str = malloc(sizeof(char) *(i + 1));
	if (str == NULL)
		return (NULL);
	while (j < i)
	{
		*(str + j) = *(line + j);
		j++;
	}
	*(str + j) = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*str;

	write(1, "> ", 2);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_read_line(line, fd);
	if (line == NULL)
		return (NULL);
	str = ft_first_line(line);
	line = ft_remove_old_line(line);
	return (str);
}