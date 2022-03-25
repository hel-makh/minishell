/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:35:11 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/25 14:21:15 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_pipe(t_cmd **cmd)
{
	int i;
	t_cmd *tmp;
	
	tmp = *cmd;
	i = 0;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type != PIPE)
			break;
		i++;
		tmp = tmp->next;
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

void	exec_loop(t_cmd *cmd, t_exec *exec, t_vars *vars)
{
	while (cmd)
	{
		if ((cmd->type == AND && exit_status != 0)
			|| (cmd->type == OR && exit_status == 0))
		{
			cmd = cmd->next;
			continue;
		}
		exec->pipes = check_pipe(&cmd);
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





































// 	pid_t pid;
// 	while (exec->i < exec->cmd_nbr)
// 	{
// 		if (cmd->type != PIPE)
// 		{
// 			exec->pipes = check_pipe(&cmd);
// 			if (exec->pipes != 0)
// 			{
// 				execute_pipes(&cmd, exec, vars);
// 				continue;
// 			}
// 		}
// 		printf("cmd now %s\n",cmd->cmd[0]);
// 		pid = fork();
// 		if (pid == -1)
// 			exit_perror();
// 		if (pid == 0)
// 		{
// 			if (cmd->type == AND)
// 			{
// 				if (exit_status == 0)
// 					exec_child_simple(cmd, exec, vars);
// 				else
// 					exit(1);
// 			}
// 			if (cmd->type == OR)
// 			{
// 				if (exit_status != 0)
// 					exec_child_simple(cmd, exec, vars);
// 				else
// 					exit(1);
// 			}
// 			exec_child_simple(cmd, exec, vars);
// 		}
// 		waitpid(pid,&exec->status,0);
// 		if (cmd->type != WORD && cmd->type != PIPE)
// 		{
// 			exit_status = WEXITSTATUS(exec->status);
// 			if (exit_status == 1)
// 			{                                                                                                                                                                
// 				if (cmd->type == AND)
// 					break;
// 			}
// 		}
// 		if (cmd->next)
// 			cmd = cmd->next;
// 		exec->i = exec->i + 1;