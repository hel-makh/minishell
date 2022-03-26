/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:35:11 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/26 13:46:28 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_output(t_list *redirect)
{
	int	fd;

	while (redirect)
	{
		if (redirect->type == RED_OUT || redirect->type == D_RED_OUT)
		{
			if (redirect->type == RED_OUT)
				fd = open(redirect->content,
						O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (redirect->type == D_RED_OUT)
				fd = open(redirect->content,
						O_RDWR | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				exit_perror();
			if (!redirect->next)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
				return (1);
			}
			close(fd);
		}
		redirect = redirect->next;
	}
	return (0);
}

int	redirect_input(t_list *redirect)
{
	int	fd;

	while (redirect)
	{
		if (redirect->type == RED_IN || redirect->type == D_RED_IN)
		{
			if (redirect->type == RED_IN)
				fd = open(redirect->content, O_RDONLY);
			// else if (redirect->type == D_RED_IN)
			// 	heredoc_exec(exec, redirect->content);
			if (fd == -1)
				exit_perror();
			if (!redirect->next)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
				return (1);
			}
			close(fd);
		}
		redirect = redirect->next;
	}
	return (0);
}

int	exec_cmd_skip(t_cmd *cmd)
{
	int	subsh_lvl;
	int	i;

	subsh_lvl = 0;
	i = 0;
	if (!cmd->subsh_lvl[0])
		return (1);
	while (1)
	{
		i ++;
		subsh_lvl += cmd->subsh_lvl[0];
		if (cmd->subsh_lvl[1])
			subsh_lvl -= cmd->subsh_lvl[1];
		if (subsh_lvl <= 0)
			break ;
		cmd = cmd->next;
	}
	return (i);
}

void	execute_cmds(t_vars *vars)
{
	t_cmd	*cmd;
	int		i;

	cmd = vars->cmds;
	while (cmd)
	{
		if ((cmd->type == AND && exit_status != 0)
			|| (cmd->type == OR && exit_status == 0))
		{
			i = exec_cmd_skip(cmd);
			while (i--)
				cmd = cmd->next;
			continue ;
		}
		exec_cmd(&cmd, vars);
		cmd = cmd->next;
	}
}
