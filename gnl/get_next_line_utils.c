/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:50:12 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/28 16:23:16 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	size;

	size = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[size + i] = src[i];
		i++;
	}
	dest[size + i] = '\0';
	return (dest);
}

int	ft_strlen(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		size1;
	int		size2;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char) * 1);
		*(s1 + 0) = '\0';
	}
	p = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	ft_strcpy(p, s1);
	ft_strcat(p, s2);
	free(s1);
	return (p);
}

char	*ft_strchr(char *s, int c)
{
	char	*b;
	int		i;
	int		len;

	if (s == NULL)
		return (0);
	b = (char *)s;
	len = ft_strlen(b);
	i = 0;
	while (i <= len)
	{
		if (*b == (char)c)
			return (b);
		i++;
		b++;
	}
	return (NULL);
}
