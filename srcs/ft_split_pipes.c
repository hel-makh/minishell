/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:13:59 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/04 14:30:56 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_split_pipelen(char const *s)
{
	int		quote;
	size_t	str_len;

	quote = 0;
	str_len = 0;
	while (s[str_len])
	{
		if (s[str_len] == '|' && !quote)
			break ;
		if (s[str_len] == '"')
			quote = !quote;
		str_len ++;
	}
	return (str_len);
}

static size_t	ft_count_pipes(char const *s)
{
	int		quote;
	size_t	count;
	size_t	i;

	quote = 0;
	count = 0;
	i = 0;
	while (s[i] && s[i] == '|')
		i ++;
	if (s[i] && s[i] != '|')
	{
		if (s[i] == '"')
			quote = 1;
		count ++;
		i ++;
	}
	while (s[i])
	{
		if (s[i - 1] == '|' && s[i] != '|' && !quote)
			count ++;
		if (s[i] == '"')
			quote = !quote;
		i ++;
	}
	return (count);
}

char	**ft_split_pipes(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	str_len;
	char	**arr;

	if (!s)
		return (0);
	arr = (char **) malloc ((ft_count_pipes(s) + 1) * sizeof(char *));
	if (arr == NULL)
		return (0);
	i = 0;
	j = 0;
	while (i < ft_count_pipes(s))
	{
		while (s[j] == '|')
			j ++;
		str_len = ft_split_pipelen(&s[j]);
		arr[i] = ft_substr(s, j, str_len);
		if (arr[i] == NULL)
			return (ft_free_2d(arr));
		j += str_len;
		i ++;
	}
	arr[i] = NULL;
	return (arr);
}
