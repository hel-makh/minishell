/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:54:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/26 12:38:31 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_pipes_count(t_cmd *cmd)
{
	int	pipes;
	int	i;

	pipes = 0;
	while (cmd)
	{
		if (cmd->type == PIPE)
			pipes ++;
		if (cmd->subsh_lvl[0])
		{
			i = exec_cmd_skip(cmd);
			while (i--)
				cmd = cmd->next;
			continue ;
		}
		cmd = cmd->next;
	}
	return (pipes);
}

void	init_pipes(t_pipe **p, int count)
{
	int		fd[2];
	t_pipe	*p_list;

	while (count--)
	{
		if (pipe(fd) == -1)
			exit_perror();
		p_list = ft_pipe_lstnew(fd[STDIN_FILENO], fd[STDOUT_FILENO]);
		if (!p_list)
			return ;
		ft_pipe_lstadd_back(p, p_list);
	}
}

void	close_pipes(t_pipe **p, int count)
{
	t_pipe	*p_list;

	if (!p || !*p)
		return ;
	while (count > 0
		|| (count == -1 && ft_pipe_lstlast(*p)))
	{
		p_list = ft_pipe_lstlast(*p);
		close(p_list->fd[STDIN_FILENO]);
		close(p_list->fd[STDOUT_FILENO]);
		if (!(*p) || !(*p)->next)
			*p = NULL;
		else
		{
			p_list = *p;
			while (p_list && p_list->next && p_list->next->next)
				p_list = p_list->next;
			p_list->next = ft_free(p_list->next);
		}
		if (count > 0)
			count --;
	}
}

void	exec_cmd_child(t_cmd *cmd, t_vars *vars)
{
	if (!redirect_input(cmd->redirect))
	{
		if (cmd->type == PIPE)
		{
			if (ft_pipe_lstlast(vars->pipes))
			{
				dup2(ft_pipe_lstlast(vars->pipes)->fd[STDIN_FILENO],
					STDIN_FILENO);
				close_pipes(&vars->pipes, 1);
			}
		}
	}
	if (!redirect_output(cmd->redirect))
	{
		if (cmd->next && cmd->next->type == PIPE)
		{
			if (ft_pipe_lstlast(vars->pipes))
			{
				dup2(ft_pipe_lstlast(vars->pipes)->fd[STDOUT_FILENO],
					STDOUT_FILENO);
				close_pipes(&vars->pipes, 1);
			}
		}
	}
	the_execution(cmd, vars);
}

void	exec_cmd(t_cmd **cmd, t_vars *vars)
{
	pid_t	pid;
	int		status;

	while (*cmd)
	{
		if ((*cmd)->next && (*cmd)->next->type == PIPE)
			init_pipes(&vars->pipes, 1);
		pid = fork();
		if (pid == -1)
			exit_perror();
		if (pid == 0)
			exec_cmd_child(*cmd, vars);
		if ((*cmd)->type == PIPE)
			close_pipes(&vars->pipes, 1);
		if (((*cmd)->next && (*cmd)->next->type != PIPE)
			&& (*cmd)->type != PIPE)
		{
			(*cmd) = (*cmd)->next;
			break ;
		}
		(*cmd) = (*cmd)->next;
	}
	waitpid(pid, &status, 0);
	exit_status = WEXITSTATUS(status);
	waitpid(-1, NULL, 0);
}
