/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:34:52 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/30 15:05:49 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_perror(void)
{
	perror ("Error");
	exit (1);
}

void	exit_cmd_notfound(char *cmd, int exit_status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (exit_status == 126)
		ft_putendl_fd(": Permission denied", 2);
	else if (exit_status == 127)
		ft_putendl_fd(": command not found", 2);
	exit(exit_status);
}

int	has_heredoc(t_list *redirect)
{
	while (redirect)
	{
		if (redirect->type == D_RED_IN)
			return (1);
		redirect = redirect->next;
	}
	return (0);
}