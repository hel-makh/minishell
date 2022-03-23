/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:50:33 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/23 10:30:09 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_delete_quotes(char *s)
{
	char	quote;
	size_t	s_len;
	size_t	quotes;
	size_t	i;

	quote = 0;
	s_len = ft_strlen(s);
	quotes = 0;
	i = 0;
	while (i < s_len)
	{
		if ((s[i] == '"' || s[i] == '\'')
			&& (!quote || (quote && quote == s[i])))
		{
			if (!quote)
				quote = s[i];
			else if (quote && quote == s[i])
				quote = 0;
			s[i] = '\0';
			quotes ++;
		}
		i ++;
	}
	return (quotes);
}

char	*ft_remove_quotes(char *s)
{
	char	*str;
	size_t	str_len;
	size_t	quotes;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	quotes = ft_delete_quotes(s);
	str = ft_calloc(str_len - quotes + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < str_len)
	{
		if (s[i])
			str[j++] = s[i];
		i ++;
	}
	s = ft_free(s);
	return (str);
}
