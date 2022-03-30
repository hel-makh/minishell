/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:54:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/30 09:46:24 by ybensell         ###   ########.fr       */
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
	if (!cmd->cmd[0]
		|| (is_built_in(cmd->cmd[0])
			&& cmd->type != PIPE
			&& (!cmd->next || (cmd->next && cmd->next->type != PIPE))))
		return (0);
	return (1);
}

static void	duplicate_pipes(t_cmd **cmd)
{
	if ((*cmd)->type == PIPE && (*cmd)->pipe[STDIN_FILENO] != -1)
	{
		if (dup2((*cmd)->pipe[STDIN_FILENO], STDIN_FILENO) == -1)
			perror("Error");
		if (close((*cmd)->pipe[STDIN_FILENO]) == -1)
			perror("Error");
	}
	if ((*cmd)->next && (*cmd)->next->type == PIPE
		&& (*cmd)->next->pipe[STDOUT_FILENO] != -1)
	{
		if (dup2((*cmd)->next->pipe[STDOUT_FILENO], STDOUT_FILENO) == -1)
			perror("Error");
		if (close((*cmd)->next->pipe[STDOUT_FILENO]) == -1)
			perror("Error");
	}
}

static void	exec_cmd_child(t_cmd *cmd, t_vars *vars, int is_fork)
{
	int	std[2];

	if (!is_fork)
	{
		std[STDIN_FILENO] = dup(STDIN_FILENO);
		std[STDOUT_FILENO] = dup(STDOUT_FILENO);
	}
	if (duplicate_redirections(&cmd, vars, is_fork))
	{
		duplicate_pipes(&cmd);
		the_execution(cmd, vars);
	}
	if (!is_fork)
	{
		dup2(std[STDIN_FILENO], STDIN_FILENO);
		close(std[STDIN_FILENO]);
		dup2(std[STDOUT_FILENO], STDOUT_FILENO);
		close(std[STDOUT_FILENO]);
	}
}
int check_heredoc(t_cmd **cmd)
{
	t_list *tmp2;
	t_cmd *tmp;

	tmp = *cmd;
	while (tmp)
	{
		tmp2 = tmp->redirect;
		while (tmp2)
		{
			if (tmp2->type == D_RED_IN)
				return (1);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

pid_t	execute_cmd(t_cmd **cmd, t_vars *vars)
{
	pid_t	pid;
	int		is_fork;

	pid = 0;
	while (*cmd)
	{
		if (check_heredoc(cmd))
			g_glob.heredoc = 1;
		is_fork = exec_is_fork(*cmd);
		if (is_fork)
		{
			signal(SIGQUIT,SIG_DFL);
			signal(SIGQUIT,signals_handler);
			pid = fork();
		}
		if (pid == -1)
			exit_perror();
		if (pid == 0)
			exec_cmd_child(*cmd, vars, is_fork);
		if ((*cmd)->type == PIPE)
			close((*cmd)->pipe[STDIN_FILENO]);
		if ((*cmd)->next && (*cmd)->next->type == PIPE)
			close((*cmd)->next->pipe[STDOUT_FILENO]);
		if (!(*cmd)->next || ((*cmd)->next && (*cmd)->next->type != PIPE))
			break ;
		(*cmd) = (*cmd)->next;
	}
	return (pid);
}
