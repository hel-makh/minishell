/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:47:56 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/27 15:06:21 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_last_redirect(t_list *redirect)
{
	int	redirect_type;

	redirect_type = redirect->type;
	redirect = redirect->next;
	while (redirect)
	{
		if (((redirect_type == RED_IN || redirect_type == D_RED_IN)
				&& (redirect->type == RED_IN || redirect->type == D_RED_IN))
			|| ((redirect_type == RED_OUT || redirect_type == D_RED_OUT)
				&& (redirect->type == RED_OUT || redirect->type == D_RED_OUT)))
			return (0);
		redirect = redirect->next;
	}
	return (1);
}

static int	open_redirect_fd(t_list *redirect)
{
	int	fd;

	fd = -1;
	if (redirect->type == RED_OUT)
		fd = open(redirect->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (redirect->type == D_RED_OUT)
		fd = open(redirect->content, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (redirect->type == RED_IN)
		fd = open(redirect->content, O_RDONLY);
	else if (redirect->type == D_RED_IN)
		fd = open_heredoc(redirect->content);
	return (fd);
}

static void	duplicate_redirect_fd(t_cmd **cmd, int fd)
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
		if ((*cmd)->next)
			(*cmd)->next->pipe[STDOUT_FILENO] = fd;
	}
}

int	duplicate_redirections(t_cmd **cmd, int is_fork)
{
	t_list	*redirect;
	int		fd;

	redirect = (*cmd)->redirect;
	while (redirect)
	{
		fd = open_redirect_fd(redirect);
		if (fd == -1)
		{
			if (is_fork)
				exit_perror();
			perror("Error");
			return (0);
		}
		if (is_last_redirect(redirect))
			duplicate_redirect_fd(cmd, fd);
		close(fd);
		redirect = redirect->next;
	}
	return (1);
}
