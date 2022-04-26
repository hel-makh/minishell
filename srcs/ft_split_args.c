/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:13:59 by hel-makh          #+#    #+#             */
/*   Updated: 2022/04/26 01:44:54 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_split_arglen(char const *s)
{
	char	quote;
	size_t	str_len;

	quote = 0;
	str_len = 0;
	while (s[str_len])
	{
		if (ft_isspace(s[str_len]) && !quote)
			break ;
		if (s[str_len] == '"' || s[str_len] == '\'')
			quote = s[str_len];
		str_len ++;
	}
	return (str_len);
}

static size_t	ft_loop_count(const char *s, size_t *index, char *quote)
{
	size_t	count;

	count = 0;
	while (s[*index])
	{
		if (!*quote && ft_isspace(s[*index - 1]) && !ft_isspace(s[*index]))
			count ++;
		if (!*quote && (s[*index] == '"' || s[*index] == '\''))
			*quote = s[*index];
		else if (*quote && s[*index] == *quote)
			*quote = 0;
		*index += 1;
	}
	return (count);
}

static size_t	ft_count_args(char const *s)
{
	char	quote;
	size_t	count;
	size_t	i;

	quote = 0;
	count = 0;
	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i ++;
	if (s[i] && !ft_isspace(s[i]))
	{
		if (s[i] == '"' || s[i] == '\'')
			quote = s[i];
		count ++;
		i ++;
	}
	count += ft_loop_count(s, &i, &quote);
	return (count);
}

char	**ft_split_args(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	str_len;
	char	**arr;

	if (!s)
		return (0);
	arr = (char **) malloc ((ft_count_args(s) + 1) * sizeof(char *));
	if (arr == NULL)
		return (0);
	i = 0;
	j = 0;
	while (i < ft_count_args(s))
	{
		while (ft_isspace(s[j]))
			j ++;
		str_len = ft_split_arglen(&s[j]);
		arr[i] = ft_substr(s, j, str_len);
		if (arr[i] == NULL)
			return (ft_free_2d(arr));
		j += str_len;
		i ++;
	}
	arr[i] = NULL;
	return (arr);
}
