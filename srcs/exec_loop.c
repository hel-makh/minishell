/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:35:11 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/25 16:48:54 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_pipe(t_cmd *cmd, int subsh_lvl)
{
	int	subsh;
	int i;
	
	subsh = 0;
	i = 0;
	while (cmd)
	{
		subsh += cmd->subsh_lvl[0];
		if (subsh == subsh_lvl && cmd->type == PIPE)
			i++;
		subsh -= cmd->subsh_lvl[1];
		cmd = cmd->next;
	}
	return (i);
}

// exec child
void	exec_child_simple(t_cmd **cmd, t_exec *exec, t_vars *vars)
{
	exec->pid = fork();
	if (exec->pid == -1)
		perror("Error");
	if (exec->pid == 0)
	{
		exec->fd_out = 1;
		exec->fd_in = 1;
		redirect_loop_input(exec, *cmd);
		dup2(exec->fd_in, 0);
		redirect_loop_output_last(exec, *cmd);
		dup2(exec->fd_out, 1);
		if ((*cmd)->cmd)
			the_execution(*cmd, vars);
		exit (0);
	}
	waitpid(exec->pid, &exec->status, 0);
	exit_status = WEXITSTATUS(exec->status);
	*cmd = (*cmd)->next;
}

int		exec_cmd_skip(t_cmd *cmd)
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

void	init_fd_cmd(t_cmd *cmd, t_exec *exec, t_vars *vars)
{
	while (cmd)
	{
		exec->pipes = check_pipe(cmd,);
	}
}

void	exec_loop(t_cmd *cmd, t_exec *exec, t_vars *vars)
{
	int	i;
	int	subsh_lvl;

	init_fd_cmd(cmd, exec, vars);
	while (cmd)
	{
		subsh_lvl += cmd->subsh_lvl[0];
		subsh_lvl -= cmd->subsh_lvl[1];
		if ((cmd->type == AND && exit_status != 0)
			|| (cmd->type == OR && exit_status == 0))
		{
			i = exec_cmd_skip(cmd);
			while (i--)
				cmd = cmd->next;
			continue;
		}
		exec->pipes = check_pipe(cmd,);
		if (exec->pipes)
			execute_pipes(&cmd, exec, vars);
		else
		{
			if (is_built_in(cmd->cmd[0]) == 0 && cmd->subsh_lvl == 0)
			{
				exit_status = exec_built_in(cmd->cmd);
				cmd = cmd->next;
			}
			else
				exec_child_simple(&cmd, exec, vars);
		}
	}
}
