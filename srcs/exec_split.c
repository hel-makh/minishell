/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:06:42 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/22 10:47:38 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	words_numb(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			i++;
		s++;
	}
	return (i);
}

static int	word_size(const char *s, char c)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0' && *(s + i) != c)
	{
		i++;
	}
	return (i);
}

static char	*fill_str(char *lil_str, const char *s, char c)
{
	int	i;

	i = 0;
	while (*s != '\0' && *s != c)
	{
		*(lil_str + i) = *s;
		i++;
		s++;
	}
	*(lil_str + i) = '/';
	*(lil_str + i + 1) = '\0';
	return (lil_str);
}

static void	*free_f(char **str, int i)
{
	while (i >= 0)
	{
		free(str + i);
		i--;
	}
	free(str);
	return (NULL);
}

char	**exec_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		words;

	if (s == NULL)
		return (NULL);
	words = words_numb(s, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (tab == 0)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s == c && *s)
			s++;
		*(tab + i) = (char *)malloc(sizeof(char) * (word_size((s), c) + 2));
		if (*(tab + i) == 0)
			return (free_f(tab, i));
		fill_str(*(tab + i), s, c);
		while (*s != c && *s)
			s++;
		i++;
	}
	*(tab + i) = 0;
	return (tab);
}
