/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:34:52 by ybensell          #+#    #+#             */
/*   Updated: 2022/04/29 00:08:47 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_error(char *cmd, char *error_msg, int exit_status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(exit_status);
}

void	exit_perror(char *error)
{
	char	*err;

	err = ft_strjoin("minishell: ", error);
	perror(err);
	err = ft_free(err);
	exit(1);
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
