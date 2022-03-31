/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:34:52 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/31 16:41:57 by hel-makh         ###   ########.fr       */
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
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, 2);
	if (exit_status == 126)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else if (exit_status == 127)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(exit_status);
}

int	exec_is_fork(t_cmd *cmd)
{
	if (!cmd->cmd[0]
		|| (is_built_in(cmd->cmd[0])
			&& cmd->type != PIPE
			&& (!cmd->next || (cmd->next && cmd->next->type != PIPE))))
		return (0);
	return (1);
}
