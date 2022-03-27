/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:47:56 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/27 12:12:46 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_open_fd(t_list *redirect)
{
	int	fd;

	if (redirect->type == RED_OUT)
		fd = open(redirect->content,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (redirect->type == D_RED_OUT)
		fd = open(redirect->content,
				O_RDWR | O_CREAT | O_APPEND, 0644);
	if (redirect->type == RED_IN)
		fd = open(redirect->content, O_RDONLY);
	// else if (redirect->type == D_RED_IN)
	// 	heredoc_exec(exec, redirect->content);
	return (fd);
}

static void	duplicate_std(t_cmd **cmd, int fd)
{
	t_list	*redirect;

	redirect = (*cmd)->redirect;
	if (redirect->type == RED_IN || redirect->type == D_RED_IN)
	{
		dup2(fd, STDIN_FILENO);
		(*cmd)->pipe[STDIN_FILENO] = fd;
	}
	else if (redirect->type == RED_OUT || redirect->type == D_RED_OUT)
	{
		dup2(fd, STDOUT_FILENO);
		(*cmd)->pipe[STDOUT_FILENO] = fd;
	}
	close(fd);
}

int	duplicate_redirections(t_cmd **cmd, int is_fork)
{
	t_list	*redirect;
	int		fd;

	redirect = (*cmd)->redirect;
	while (redirect)
	{
		fd = ft_open_fd(redirect);
		if (fd == -1)
		{
			if (is_fork)
				exit_perror();
			perror("Error");
			return (0);
		}
		if (!redirect->next)
		{
			duplicate_std(cmd, fd);
			return (1);
		}
		close(fd);
		redirect = redirect->next;
	}
	return (1);
}
