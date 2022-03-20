/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:24:45 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/04 14:44:29 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_exec_first_cmd(t_vars *vars, char **cmd)
{
	int		fd;

	close(vars->p[STDIN_FILENO]);
	if (dup2(vars->p[STDOUT_FILENO], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(vars->p[STDOUT_FILENO]);
	if (vars->redirect_input)
	{
		fd = open(vars->redirect_input, O_RDONLY);
		if (fd == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd);
	}
	if (execve(cmd[0], cmd, vars->envp) == -1)
		perror("execve");
	cmd = ft_free_2d(cmd);
	exit(EXIT_FAILURE);
}

static void	ft_exec_middle_cmd(t_vars *vars, char **cmd)
{
	if (dup2(vars->p[STDIN_FILENO], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(vars->p[STDIN_FILENO]);
	if (dup2(vars->p[STDOUT_FILENO], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(vars->p[STDOUT_FILENO]);
	if (execve(cmd[0], cmd, vars->envp) == -1)
		perror("execve");
	cmd = ft_free_2d(cmd);
	exit(EXIT_FAILURE);
}

static void	ft_exec_last_cmd(t_vars *vars, char **cmd)
{
	int		fd;

	close(vars->p[STDOUT_FILENO]);
	if (dup2(vars->p[STDIN_FILENO], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(vars->p[STDIN_FILENO]);
	if (vars->redirect_output || vars->redirect_append)
	{
		if (vars->redirect_output)
			fd = open(vars->redirect_output,
					O_RDWR | O_TRUNC | O_CREAT, 0644);
		else
			fd = open(vars->redirect_append,
					O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd);
	}
	if (execve(cmd[0], cmd, vars->envp) == -1)
		perror("execve");
	cmd = ft_free_2d(cmd);
	exit(EXIT_FAILURE);
}

static void	ft_exec_sole_cmd(t_vars *vars, char **cmd)
{
	int		fd[2];

	if (vars->redirect_input)
	{
		fd[STDIN_FILENO] = open(vars->redirect_input, O_RDONLY);
		if (fd[STDIN_FILENO] == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd[STDIN_FILENO], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd[STDIN_FILENO]);
	}
	if (vars->redirect_output || vars->redirect_append)
	{
		if (vars->redirect_output)
			fd[STDOUT_FILENO] = open(vars->redirect_output,
					O_RDWR | O_TRUNC | O_CREAT, 0644);
		else
			fd[STDOUT_FILENO] = open(vars->redirect_append,
					O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd[STDOUT_FILENO] == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd[STDOUT_FILENO]);
	}
	if (execve(cmd[0], cmd, vars->envp) == -1)
		perror("execve");
	cmd = ft_free_2d(cmd);
	exit(EXIT_FAILURE);
}

void	ft_exec_pipeline(t_vars *vars, int index)
{
	char	**cmd;

	cmd = ft_execve_args(vars, vars->pipeline[index]);
	if (!cmd)
		exit(EXIT_FAILURE);
	if (vars->cmd_count == 1)
		ft_exec_sole_cmd(vars, cmd);
	else
	{
		if (index == 0)
			ft_exec_first_cmd(vars, cmd);
		else if (index == vars->cmd_count - 1)
			ft_exec_last_cmd(vars, cmd);
		else
			ft_exec_middle_cmd(vars, cmd);
	}
}
