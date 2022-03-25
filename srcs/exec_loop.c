/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:35:11 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/25 17:32:52 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int check_pipe(t_cmd *cmd)
{
	int	subsh;
	int j;
	int i;
	
	subsh = 0;
	i = 0;
	j = 0;
	while (cmd)
	{
		if (cmd->subsh_lvl[0])
			i = exec_cmd_skip(cmd);
		while (i--)
				cmd = cmd->next;
		continue
		if (cmd->type == PIPE)
			j++;
		cmd = cmd->next;
	}
	return (j);
}

void	init_fd_cmd(t_cmd *cmd, t_exec *exec, t_vars *vars)
{
	int pipe_flag;

	pipe_flag = 0;
	exec->fd = ft_calloc(exec->total_pipes + 1,sizeof(int *));
	if (!exec->fd)
		exit_perror();
	exec->count = 0;
	while (cmd)
	{
		exec->pipes = check_pipe(cmd);
		init_pipes(exec);
		exec->count++;
	}
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


int get_nbr_pipes(t_cmd *cmd,t_exec *exec)
{
	int i;

	i = 0;
	while (cmd)
	{
		if (cmd->type == PIPE)
			i++;
		cmd = cmd->next;
	}
	return (i);
}

void	exec_loop(t_cmd *cmd, t_exec *exec, t_vars *vars)
{
	int	i;

	exec->total_pipes = get_nbr_pipes(cmd);
	if (exec->total_pipes)
		init_fd_cmd(cmd, exec, vars);
	while (cmd)
	{
		if ((cmd->type == AND && exit_status != 0)
			|| (cmd->type == OR && exit_status == 0))
		{
			i = exec_cmd_skip(cmd);
			while (i--)
				cmd = cmd->next;
			continue;
		}
		exec->pipes = check_pipe(cmd);
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
