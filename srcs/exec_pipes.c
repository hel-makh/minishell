/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:54:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/04/05 16:50:17 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_pipes(t_cmd **cmd)
{
	t_cmd	*cmd_t;

	cmd_t = *cmd;
	while (cmd_t)
	{
		cmd_t->pipe[STDIN_FILENO] = -1;
		cmd_t->pipe[STDOUT_FILENO] = -1;
		cmd_t->heredoc[STDIN_FILENO] = -1;
		cmd_t->heredoc[STDOUT_FILENO] = -1;
		cmd_t = cmd_t->next;
	}
}

void	ft_close_pipes(t_cmd *cmd)
{
	if (cmd->type == PIPE && cmd->pipe[STDIN_FILENO] != -1)
	{
		close(cmd->pipe[STDIN_FILENO]);
		cmd->pipe[STDIN_FILENO] = -1;
	}
	if (cmd->next && cmd->next->type == PIPE
		&& cmd->next->pipe[STDOUT_FILENO] != -1)
	{
		close(cmd->next->pipe[STDOUT_FILENO]);
		cmd->next->pipe[STDOUT_FILENO] = -1;
	}
	if (cmd->heredoc[STDIN_FILENO] != -1)
	{
		close(cmd->heredoc[STDIN_FILENO]);
		cmd->heredoc[STDIN_FILENO] = -1;
	}
	if (cmd->heredoc[STDOUT_FILENO] != -1)
	{
		close(cmd->heredoc[STDOUT_FILENO]);
		cmd->heredoc[STDOUT_FILENO] = -1;
	}
}

int	exec_init_pipes(t_cmd **cmd)
{
	t_cmd	*cmd_t;

	cmd_t = *cmd;
	while (cmd_t)
	{
		if (cmd_t->type == PIPE)
		{
			if (pipe(cmd_t->pipe) == -1)
				return (perror("pipe"), 0);
		}
		cmd_t = cmd_t->next;
	}
	return (1);
}

static void	duplicate_pipes(t_cmd **cmd)
{
	if ((*cmd)->type == PIPE && (*cmd)->pipe[STDIN_FILENO] != -1)
	{
		if (dup2((*cmd)->pipe[STDIN_FILENO], STDIN_FILENO) == -1)
			exit_perror("dup2");
		if (close((*cmd)->pipe[STDIN_FILENO]) == -1)
			exit_perror("close");
		else
			(*cmd)->pipe[STDIN_FILENO] = -1;
	}
	if ((*cmd)->next && (*cmd)->next->type == PIPE
		&& (*cmd)->next->pipe[STDOUT_FILENO] != -1)
	{
		if ((*cmd)->next->pipe[STDIN_FILENO] != -1
			&& close((*cmd)->next->pipe[STDIN_FILENO]) == -1)
			exit_perror("close");
		else
			(*cmd)->next->pipe[STDIN_FILENO] = -1;
		if (dup2((*cmd)->next->pipe[STDOUT_FILENO], STDOUT_FILENO) == -1)
			exit_perror("dup2");
		if (close((*cmd)->next->pipe[STDOUT_FILENO]) == -1)
			exit_perror("close");
		else
			(*cmd)->next->pipe[STDOUT_FILENO] = -1;
	}
}

void	exec_cmd_child(t_cmd *cmd, t_vars *vars, int is_fork)
{
	int	std[2];

	if (is_fork)
	{
		signal(SIGINT, signal_child);
		signal(SIGQUIT, signal_child);
	}
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
