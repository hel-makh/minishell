/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:47:56 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/27 18:54:01 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	duplicate_redirect_fd(t_cmd **cmd, int *fd)
{
	dup2(fd[STDIN_FILENO], STDIN_FILENO);
	if (fd[STDIN_FILENO] != STDIN_FILENO)
		(*cmd)->pipe[STDIN_FILENO] = fd[STDIN_FILENO];
	dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
	if (fd[STDOUT_FILENO] != STDOUT_FILENO && (*cmd)->next)
		(*cmd)->next->pipe[STDOUT_FILENO] = fd[STDOUT_FILENO];
}

static void	open_redirect_fd(t_list *redirect, t_vars *vars, int *fd)
{
	if (redirect->type == RED_OUT)
		fd[STDOUT_FILENO] = open(redirect->content,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (redirect->type == D_RED_OUT)
		fd[STDOUT_FILENO] = open(redirect->content,
				O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (redirect->type == RED_IN)
		fd[STDIN_FILENO] = open(redirect->content, O_RDONLY);
	else if (redirect->type == D_RED_IN)
		fd[STDIN_FILENO] = open_heredoc(redirect->content, vars->envp);
}

int	duplicate_redirections(t_cmd **cmd, t_vars *vars, int is_fork)
{
	t_list	*redirect;
	int		fd[2];

	fd[STDIN_FILENO] = STDIN_FILENO;
	fd[STDOUT_FILENO] = STDOUT_FILENO;
	redirect = (*cmd)->redirect;
	while (redirect)
	{
		open_redirect_fd(redirect, vars, fd);
		if (fd[STDIN_FILENO] == -1 || fd[STDOUT_FILENO] == -1)
		{
			if (is_fork)
				exit_perror();
			perror("Error");
			return (0);
		}
		redirect = redirect->next;
	}
	duplicate_redirect_fd(cmd, fd);
	return (1);
}
