/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:39:48 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/20 14:13:39 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_str2chr(const char *s, const char *s2)
{
	int	i;

	if (!s[0] || !s[1])
		return (NULL);
	i = 0;
	while (s2[i])
	{
		if ((s[0] == s2[i] && s[1] == s2[i]))
			return ((char *)&s[0]);
		i ++;
	}
	return (NULL);
}

static int	ft_get_token_type(char *token_data)
{
	if (!ft_strcmp(token_data, "\""))
		return (D_QUOTE);
	else if (!ft_strcmp(token_data, "'"))
		return (S_QUOTE);
	else if (!ft_strcmp(token_data, "("))
		return (R_PAREN);
	else if (!ft_strcmp(token_data, ")"))
		return (L_PAREN);
	else if (!ft_strcmp(token_data, "<<"))
		return (D_RED_IN);
	else if (!ft_strcmp(token_data, "<"))
		return (RED_IN);
	else if (!ft_strcmp(token_data, ">>"))
		return (D_RED_OUT);
	else if (!ft_strcmp(token_data, ">"))
		return (RED_OUT);
	else if (!ft_strcmp(token_data, "&&"))
		return (AND);
	else if (!ft_strcmp(token_data, "||"))
		return (OR);
	else if (!ft_strcmp(token_data, "|"))
		return (PIPE);
	else if (!ft_strcmp(token_data, "*"))
		return (WILDCARD);
	return (WORD);
}

static size_t	ft_get_token_size(t_vars *vars, int i)
{
	char	*cmd;
	char	quote;
	size_t	size;

	cmd = vars->cmdline;
	quote = 0;
	size = 0;
	while (cmd[++i])
	{
		size ++;
		if (!quote && (cmd[i] == '\'' || cmd[i] == '"')
			&& cmd[i + 1] && !ft_strchr(&cmd[i + 1], cmd[i]))
		{
			if (size == 1)
				return (size);
			return (size - 1);
		}
		if (!quote && (cmd[i] == '\'' || cmd[i] == '"'))
			quote = cmd[i];
		else if (quote)
		{
			if (cmd[i] == quote)
				quote = 0;
			continue ;
		}
		if (ft_str2chr(&cmd[i], "<>&|"))
		{
			if (size == 1)
				return (size + 1);
			return (size - 1);
		}
		else if (ft_strchr(" ()<>|*", cmd[i]))
		{
			if (size == 1)
				return (size);
			return (size - 1);
		}
	}
	return (size);
}

void	ft_tokenization(t_vars *vars)
{
	int		i;
	size_t	size;
	char	*token_data;
	int		token_type;

	ft_token_lstclear(&vars->tokens);
	i = 0;
	while (vars->cmdline[i])
	{
		if (vars->cmdline[i] != ' ')
		{
			size = ft_get_token_size(vars, i - 1);
			token_data = ft_substr(vars->cmdline, i, size);
			token_type = ft_get_token_type(token_data);
			ft_token_lstadd_back(&vars->tokens,
				ft_token_lstnew(token_data, token_type));
			i += size - 1;
		}
		i ++;
	}
}
