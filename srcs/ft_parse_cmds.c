/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:11:41 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/21 14:11:21 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_parse_cmds(t_vars *vars)
{
	t_cmd		*temp_cmd;
	t_list		*t_tokens;
	int			paren_closed;

	temp_cmd = ft_cmd_lstnew(ft_calloc(1, sizeof(char *)), 0, 0, NULL);
	if (!temp_cmd->cmd)
		return (0);
	paren_closed = 0;
	t_tokens = vars->tokens;
	while (t_tokens)
	{
		if (t_tokens->type == WORD)
		{
			temp_cmd->cmd = ft_add_str2arr(temp_cmd->cmd, t_tokens->content);
			if (!temp_cmd->cmd)
				return (0);
		}
		if (t_tokens->type == L_PAREN)
			temp_cmd->subsh_lvl ++;
		if (t_tokens->type == RED_IN || t_tokens->type == RED_OUT
			|| t_tokens->type == D_RED_IN || t_tokens->type == D_RED_OUT)
		{
			ft_lstadd_back(&temp_cmd->redirect,
				ft_lstnew(ft_strdup(t_tokens->next->content), t_tokens->type));
			t_tokens = t_tokens->next->next;
			continue ;
		}
		if (t_tokens->type == PIPE || t_tokens->type == OR
			|| t_tokens->type == AND || !t_tokens->next)
		{
			ft_cmd_lstadd_back(&vars->cmds, temp_cmd);
			if (t_tokens->next)
			{
				temp_cmd = ft_cmd_lstnew(ft_calloc(1, sizeof(char *)),
						t_tokens->type, temp_cmd->subsh_lvl, NULL);
				if (!temp_cmd->cmd)
					return (0);
			}
			if (paren_closed)
			{
				temp_cmd->subsh_lvl -= paren_closed;
				paren_closed = 0;
			}
		}
		if (t_tokens->type == R_PAREN)
			paren_closed ++;
		t_tokens = t_tokens->next;
	}
	return (1);
}
