/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:18:40 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/27 14:26:10 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define HEREDOC "/tmp/.minishell_hh_heredoctmp_78979346245648"

int	open_heredoc(char *limiter)
{
	int		fd;
	char	*heredoc;
	char	*heredoc_file;

	fd = open(HEREDOC, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (fd);
	heredoc = NULL;
	heredoc_file = ft_strdup("");
	while (1)
	{
		heredoc = ft_free(heredoc);
		heredoc = readline("> ");
		if (!heredoc || ft_strcmp(heredoc, limiter) == 0)
			break ;
		heredoc = ft_stradd(heredoc, "\n");
		heredoc_file = ft_stradd(heredoc_file, heredoc);
	}
	ft_putstr_fd(heredoc_file, fd);
	heredoc = ft_free(heredoc);
	heredoc_file = ft_free(heredoc_file);
	fd = open(HEREDOC, O_RDONLY);
	if (fd == -1 || unlink(HEREDOC) == -1)
		return (-1);
	return (fd);
}
