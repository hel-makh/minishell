/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:46:03 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/24 17:46:17 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_built_in(char *name)
{
	if (!name)
		return (1);
	if (ft_strcmp(name, "echo") == 0
		|| ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "pwd") == 0
		|| ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0
		|| ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "exit") == 0)
		return (0);
	else
		return (1);
}

int	exec_built_in(char **cmd)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd[0], "echo") == 0)
		status = echo_builtin(cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		status = cd_build(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		status = pwd_cmd();
	/*
	else if (ft_strcmp(cmd[0], "export") == 0)
		status = export_cmd(ac, av, env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		status = exit_cmd(ac, av);
	else if (ft_strcmp(cmd[0], "env") == 0)
		status = cmd_env(ac, env);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		status = cmd_unset(ac, av, env);
	*/
	return (status);
}