/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wc_strcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:19:43 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/22 12:24:08 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_strnotchr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == c)
		i ++;
	return ((char *)&s[i]);
}

static void	ft_skip_wildcards(
	const char *s1, const char *s2, size_t *i, size_t *j
	)
{
	char	*(*search_func)(const char *, int);
	char	*str;

	str = ft_strnotchr(&s1[*i + 1], '*');
	if (str && ft_strchr(str, '*'))
		search_func = &ft_strchr;
	else
		search_func = &ft_strrchr;
	if (!ft_strchr(&s2[*j], str[0]))
		return ;
	while (s1[*i] == '*'
		&& *j < ft_strlen(s2) - ft_strlen(search_func(&s2[*j], str[0])))
		*j += 1;
	if (str[0] == s2[*j]
		&& *j == ft_strlen(s2) - ft_strlen(search_func(&s2[*j], str[0])))
		while (s1[*i] == '*')
			*i += 1;
}

int	ft_wc_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] || s2[j])
	{
		if (s1[i] != '*' && s1[i] != s2[j])
			break ;
		ft_skip_wildcards(s1, s2, &i, &j);
		if (s1[i])
			i ++;
		if (s2[j])
			j ++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}
