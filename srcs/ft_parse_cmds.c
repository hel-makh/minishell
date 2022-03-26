/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:11:41 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/26 21:40:42 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_add_cmd(t_vars *vars, t_cmd **cmd, t_list **token)
{
	if ((*token)->type == RED_IN || (*token)->type == RED_OUT
		|| (*token)->type == D_RED_IN || (*token)->type == D_RED_OUT)
	{
		ft_lstadd_back(&(*cmd)->redirect,
			ft_lstnew(ft_strdup((*token)->next->content), (*token)->type));
		if (!ft_lstlast((*cmd)->redirect)->content)
			return (0);
		*token = (*token)->next;
	}
	if (!(*token)->next || (*token)->type == AND
		|| (*token)->type == OR || (*token)->type == PIPE)
	{
		ft_cmd_lstadd_back(&vars->cmds, *cmd);
		if ((*token)->next)
		{
			*cmd = ft_cmd_lstnew(ft_calloc(1, sizeof(char *)),
					(*token)->type, ft_calloc(2, sizeof(int)), NULL);
			if (!(*cmd) || !(*cmd)->cmd || !(*cmd)->subsh_lvl)
				return (0);
		}
	}
	return (1);
}

int	ft_parse_cmds(t_vars *vars)
{
	t_cmd		*cmd;
	t_list		*token;

	cmd = ft_cmd_lstnew(ft_calloc(1, sizeof(char *)), 0,
			ft_calloc(2, sizeof(int)), NULL);
	if (!cmd || !cmd->cmd || !cmd->subsh_lvl)
		return (0);
	token = vars->tokens;
	while (token)
	{
		if (token->type == WORD)
		{
			cmd->cmd = ft_add_str2arr(cmd->cmd, token->content);
			if (!cmd->cmd)
				return (0);
		}
		if (token->type == L_PAREN)
			cmd->subsh_lvl[0]++;
		if (token->type == R_PAREN)
			cmd->subsh_lvl[1]++;
		if (!ft_add_cmd(vars, &cmd, &token))
			return (0);
		token = token->next;
	}
	return (1);
}
