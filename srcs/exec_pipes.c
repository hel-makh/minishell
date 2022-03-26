/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:54:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/26 20:59:10 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_init_pipes(t_cmd **cmd)
{
	t_cmd	*cmd_t;

	cmd_t = *cmd;
	while (cmd_t)
	{
		if (cmd_t->type == PIPE)
		{
			if (pipe(cmd_t->pipe) == -1)
			{
				cmd_t->pipe[STDIN_FILENO] = -1;
				cmd_t->pipe[STDOUT_FILENO] = -1;
				perror("Error");
				return (0);
			}
		}
		else
		{
			cmd_t->pipe[STDIN_FILENO] = -1;
			cmd_t->pipe[STDOUT_FILENO] = -1;
		}
		cmd_t = cmd_t->next;
	}
	return (1);
}

static int	exec_is_fork(t_cmd *cmd)
{
	if (((cmd->next && cmd->next->type == PIPE)
			|| cmd->type == PIPE)
		|| ((!cmd->next || (cmd->next && cmd->next->type != PIPE))
			&& cmd->type != PIPE
			&& !is_built_in(cmd->cmd[0])))
		return (1);
	return (0);
}

static void	exec_cmd_child(t_cmd *cmd, t_vars *vars)
{
	if (!redirect_input(cmd->redirect))
	{
		if (cmd->type == PIPE)
		{
			if (dup2(cmd->pipe[STDIN_FILENO], STDIN_FILENO) == -1)
				perror("Error");
			if (close(cmd->pipe[STDIN_FILENO]) == -1)
				perror("Error");
		}
	}
	if (!redirect_output(cmd->redirect))
	{
		if (cmd->next && cmd->next->type == PIPE)
		{
			if (dup2(cmd->next->pipe[STDOUT_FILENO], STDOUT_FILENO) == -1)
				perror("Error");
			if (close(cmd->next->pipe[STDOUT_FILENO]) == -1)
				perror("Error");
		}
	}
	the_execution(cmd, vars);
}

pid_t	exec_cmd(t_cmd **cmd, t_vars *vars)
{
	pid_t	pid;
	int		is_fork;

	pid = 0;
	while (*cmd)
	{
		is_fork = exec_is_fork(*cmd);
		if (is_fork)
			pid = fork();
		if (pid == -1)
			exit_perror();
		if (pid == 0)
			exec_cmd_child(*cmd, vars);
		if ((*cmd)->type == PIPE)
			close((*cmd)->pipe[STDIN_FILENO]);
		if ((*cmd)->next && (*cmd)->next->type == PIPE)
			close((*cmd)->next->pipe[STDOUT_FILENO]);
		if (!(*cmd)->next || ((*cmd)->next && (*cmd)->next->type != PIPE))
			break ;
		(*cmd) = (*cmd)->next;
	}
	if (is_fork)
		return (pid);
	return (0);
}
