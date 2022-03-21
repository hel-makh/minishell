/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:39:48 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/21 16:34:33 by hel-makh         ###   ########.fr       */
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

static size_t	ft_end_of_token(char *cmd, size_t size)
{
	if (ft_str2chr(cmd, "<>&|"))
	{
		if (size == 1)
			return (size + 1);
		return (size - 1);
	}
	else if (ft_strchr(" ()<>|", cmd[0]) || ((cmd[0] == '\'' || cmd[0] == '"')
			&& (!cmd[1] || (cmd[1] && !ft_strchr(&cmd[1], cmd[0])))))
	{
		if (size == 1)
			return (size);
		return (size - 1);
	}
	return (0);
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
		if (!quote && (cmd[i] == '\'' || cmd[i] == '"'))
			quote = cmd[i];
		else if (quote)
		{
			if (cmd[i] == quote)
				quote = 0;
			continue ;
		}
		if (ft_end_of_token(&cmd[i], size))
			return (ft_end_of_token(&cmd[i], size));
	}
	return (size);
}

static int	ft_get_token_type(char *token_content)
{
	if (!ft_strcmp(token_content, "\""))
		return (D_QUOTE);
	else if (!ft_strcmp(token_content, "'"))
		return (S_QUOTE);
	else if (!ft_strcmp(token_content, "("))
		return (L_PAREN);
	else if (!ft_strcmp(token_content, ")"))
		return (R_PAREN);
	else if (!ft_strcmp(token_content, "<<"))
		return (D_RED_IN);
	else if (!ft_strcmp(token_content, "<"))
		return (RED_IN);
	else if (!ft_strcmp(token_content, ">>"))
		return (D_RED_OUT);
	else if (!ft_strcmp(token_content, ">"))
		return (RED_OUT);
	else if (!ft_strcmp(token_content, "&&"))
		return (AND);
	else if (!ft_strcmp(token_content, "||"))
		return (OR);
	else if (!ft_strcmp(token_content, "|"))
		return (PIPE);
	return (WORD);
}

void	ft_tokenization(t_vars *vars)
{
	size_t	size;
	char	*token_content;
	int		token_type;
	int		i;

	i = 0;
	while (vars->cmdline[i])
	{
		if (vars->cmdline[i] != ' ')
		{
			size = ft_get_token_size(vars, i - 1);
			token_content = ft_substr(vars->cmdline, i, size);
			token_type = ft_get_token_type(token_content);
			ft_lstadd_back(&vars->tokens, ft_lstnew(token_content, token_type));
			i += size - 1;
		}
		i ++;
	}
}
