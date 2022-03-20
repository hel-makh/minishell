/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:11:41 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/20 20:01:16 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_parse_args(t_vars *vars)
{
	char		**cmd;
	t_cmd		temp_cmd;
	t_list		*t_tokens;
	int			paren_closed;

	cmd = (char **) ft_calloc(1, sizeof(char *));
	if (!cmd)
		return (0);
	temp_cmd.type = 0;
	temp_cmd.shlvl = 0;
	temp_cmd.redirect = NULL;
	paren_closed = 0;
	t_tokens = vars->tokens;
	while (t_tokens)
	{
		if (t_tokens->type == WORD)
		{
			cmd = ft_add_str2arr(cmd, t_tokens->content);
			if (!cmd)
				return (0);
		}
		if (t_tokens->type == L_PAREN)
			temp_cmd.shlvl ++;
		if (t_tokens->type == RED_IN || t_tokens->type == RED_OUT
			|| t_tokens->type == D_RED_IN || t_tokens->type == D_RED_OUT)
			ft_lstadd_back(&vars->cmds->redirect,
				ft_lstnew(t_tokens->next->content, t_tokens->type));
		if (t_tokens->type == PIPE || t_tokens->type == OR
			|| t_tokens->type == AND || !t_tokens->next)
		{
			ft_cmd_lstadd_back(&vars->cmds,
				ft_cmd_lstnew(cmd, temp_cmd.type, temp_cmd.shlvl, temp_cmd.redirect));
			temp_cmd.type = t_tokens->type;
			if (t_tokens->next)
			{
				cmd = (char **) ft_calloc(1, sizeof(char *));
				if (!cmd)
					return (0);
			}
			if (paren_closed)
			{
				temp_cmd.shlvl -= paren_closed;
				paren_closed = 0;
			}
		}
		if (t_tokens->type == R_PAREN)
			paren_closed ++;
		t_tokens = t_tokens->next;
	}
	return (1);
}
