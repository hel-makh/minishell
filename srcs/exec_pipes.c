/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:54:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/24 15:47:18 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipes(t_exec *exec)
{
	int i;
	
	i = 0;
	while (i < (2 * (exec->pipes + 1))) 
	{
        if (close(exec->fd[i]) == -1)
			exit_perror();
		i++;
    }
}

void	redirect_loop_output_last(t_exec *exec, t_cmd *cmd)
{
	t_list	*tmp;

	tmp = cmd->redirect;
	while (tmp)
	{
		if (tmp->type == RED_OUT)
		{
			exec->fd_out = open(tmp->content,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (exec->fd_out == -1)
				exit_perror();
		}
		else if (tmp->type == D_RED_OUT)
		{
			exec->fd_out = open(tmp->content,
					O_RDWR | O_CREAT | O_APPEND, 0644);
			if (exec->fd_out == -1)
				exit_perror();
		}
		tmp = tmp->next;
	}
}

void	redirect_loop_output(t_exec *exec, t_cmd *cmd)
{
	t_list	*tmp;

	tmp = cmd->redirect;
	while (tmp)
	{
		if (tmp->type == RED_OUT)
		{
			exec->fd_out = open(tmp->content,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (exec->fd_out == -1)
				exit_perror();
		}
		else if (tmp->type == D_RED_OUT)
		{
			exec->fd_out = open(tmp->content,
					O_RDWR | O_CREAT | O_APPEND, 0644);
			if (exec->fd_out == -1)
				exit_perror();
		}
		tmp = tmp->next;
	}
}

void	redirect_loop_input(t_exec *exec, t_cmd *cmd)
{
	t_list	*tmp;

	tmp = cmd->redirect;
	while (tmp)
	{
		if (tmp->type == RED_IN)
		{
			exec->fd_in = open(tmp->content, O_RDONLY);
			if (exec->fd_in == -1)
				exit_perror();
		}
		else if (tmp->type == D_RED_IN)
		{
			heredoc_exec(exec, tmp->content);
		}
		tmp = tmp->next;
	}
}

void	exec_child(t_cmd *cmd, t_exec *exec, t_vars *vars)
{
	
	if (cmd->next != NULL && cmd->next->type == PIPE)
		exec->fd_out = exec->fd[exec->j + 1];
	if (exec->j != 0)
		exec->fd_in = exec->fd[exec->j - 2];
	redirect_loop_input(exec, cmd);
	dup2(exec->fd_in, 0);
	if ((exec->i + 1) < (exec->pipes + 1))// not last command
	{
		redirect_loop_output(exec, cmd);
		dup2(exec->fd_out, 1);
	}
	else if ((exec->i + 1) == exec->pipes + 1)// last command
	{
		exec->fd_out = 1;
		redirect_loop_output_last(exec, cmd);
		dup2(exec->fd_out, 1);
	}
	close_pipes(exec);
	the_execution(cmd, vars);
}
void init_pipes(t_exec *exec)
{
	int i;
	
	i = 0;
	exec->fd = malloc(((exec->pipes + 1)  * 2) * sizeof(int));
	if (!exec->fd)
		return ;
	while (i < exec->pipes + 1)
	{
		if(pipe(exec->fd + (i * 2)) < 0)
    		perror("Error");
		i++;
	}
	exec->i = 0;
	exec->j = 0;
	exec->fd_in = 0;
	exec->fd_out = 1;
}


void	execute_pipes(t_cmd **cmd,t_exec *exec,t_vars *vars)
{
	int i;

	init_pipes(exec);
	i = 0;
	while (i < (exec->pipes + 1))
	{
		exec->pid = fork();
		if (exec->pid == -1)
			exit_perror();
		if (exec->pid == 0)
			exec_child(*cmd, exec, vars);
		(*cmd) = (*cmd)->next;
		exec->j = exec->j + 2;
		exec->i++;
		i++;
	}
	close_pipes(exec);
	waitpid(exec->pid, &exec->status, 0);
	exit_status = WEXITSTATUS(exec->status);
	waitpid(-1, NULL, 0);
	free(exec->fd);
}