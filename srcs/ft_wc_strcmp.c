/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wc_strcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:19:43 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/23 12:48:03 by hel-makh         ###   ########.fr       */
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
	char	*str;
	char	*(*search_func)(const char *, int);

	str = ft_strnotchr(&s1[*i + 1], '*');
	str = ft_remove_quotes(ft_strdup(str));
	if (str && ft_strchr(str, '*'))
		search_func = &ft_strchr;
	else
		search_func = &ft_strrchr;
	if (ft_strchr(&s2[*j], str[0]))
	{
		while (s1[*i] == '*'
			&& *j < ft_strlen(s2) - ft_strlen(search_func(&s2[*j], str[0])))
			*j += 1;
		while (s2[*j] == str[0] && s1[*i] == '*')
			*i += 1;
		*i -= 1;
		*j -= 1;
	}
	str = ft_free(str);
}

static int	ft_is_quoted(const char *s, size_t *index, char *quote)
{
	if (!*quote
		&& (s[*index] == '\'' || s[*index] == '"')
		&& ft_strchr(&s[*index + 1], s[*index]))
	{
		*quote = s[*index];
		*index += 1;
		return (1);
	}
	else if (*quote && s[*index] == *quote)
	{
		*quote = 0;
		*index += 1;
		return (1);
	}
	return (0);
}

int	ft_wc_strcmp(const char *s1, const char *s2)
{
	char	quote;
	size_t	i;
	size_t	j;

	quote = 0;
	i = 0;
	j = 0;
	while (s1[i] || s2[j])
	{
		if (ft_is_quoted(s1, &i, &quote))
			continue ;
		if (s1[i] != s2[j] && (quote || (!quote && s1[i] != '*')))
			break ;
		if (!quote && s1[i] == '*')
			ft_skip_wildcards(s1, s2, &i, &j);
		if (s1[i])
			i ++;
		if (s2[j])
			j ++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}
