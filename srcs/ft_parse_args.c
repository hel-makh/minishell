/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:11:41 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/20 17:51:17 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_pipe_count(t_list *tokens)
{
	size_t	pipe;

	pipe = 1;
	while (tokens)
	{
		if (tokens->type == PIPE)
			pipe ++;
		tokens = tokens->next;
	}
	return (pipe);
}

static size_t	ft_cmd_count(t_list *tokens, int cmd_no)
{
	size_t	cmd;
	int		i;

	cmd = 1;
	while (tokens && i <= cmd_no)
	{
		if (tokens->type == PIPE)
			i ++;
		if (i == cmd_no)
		{
			if (tokens->type == AND || tokens->type == OR)
				cmd ++;
		}
		tokens = tokens->next;
	}
	return (cmd);
}

int	ft_parse_args(t_vars *vars)
{
	size_t	pipe_count;
	int		i;

	pipe_count = ft_pipe_count(vars->tokens);
	vars->cmds = ft_calloc(pipe_count, sizeof(t_cmds));
	if (!vars->cmds)
		return (0);
	i = 0;
	while (i < pipe_count)
	{

		i ++;
	}
	return (1);
}
