/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:35:11 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/26 21:04:32 by hel-makh         ###   ########.fr       */
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

static int	ft_next_cmd(t_cmd *cmd)
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

static int	handle_operators(t_cmd **cmd)
{
	int	i;

	if (((*cmd)->type == AND && exit_status != 0)
		|| ((*cmd)->type == OR && exit_status == 0))
	{
		i = ft_next_cmd((*cmd));
		while (i--)
			(*cmd) = (*cmd)->next;
		return (1);
	}
	return (0);
}

void	execute_cmds(t_vars *vars)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		status;

	exec_init_pipes(&vars->cmds);
	cmd = vars->cmds;
	while (cmd)
	{
		if (handle_operators(&cmd))
			continue ;
		pid = exec_cmd(&cmd, vars);
		if (pid)
		{
			waitpid(pid, &status, 0);
			exit_status = WEXITSTATUS(status);
			waitpid(-1, NULL, 0);
		}
		cmd = cmd->next;
	}
}
