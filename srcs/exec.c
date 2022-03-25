/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:35:04 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/25 16:23:21 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_cmd(t_cmd *cmd, t_vars *vars)
{
	char	*cmd_temp;
	char	*path;
	char	**paths;

	path = ft_getenv("PATH", vars->envp);
	if (!path)
		exit_cmd_notfound(cmd->cmd[0], 127);
	paths = ft_split(path, ':');
	if (!paths)
		exit_perror();
	cmd_temp = find_path(paths, cmd->cmd[0]);
	paths = ft_free_2d(paths);
	if (!cmd_temp)
		exit_cmd_notfound(cmd->cmd[0], 127);
	return (cmd_temp);
}

void	the_execution(t_cmd *cmd, t_vars *vars)
{
	char	*tmp;

	tmp = NULL;
	if (is_built_in(cmd->cmd[0]) == 0)
	{
	 	if (exec_built_in(cmd->cmd) == 0)
	 		exit (0);
	 	else
	 		exit (1);
	}
	if (access(cmd->cmd[0], F_OK) == 0
		&& access(cmd->cmd[0], X_OK) == 0)
		tmp = cmd->cmd[0];
	else
		tmp = find_cmd(cmd, vars);
	if ((execve(tmp, cmd->cmd, ft_env_lstlast(vars->envp)->envp) == -1))
		exit_perror();
}

void	execute_cmd(t_cmd *cmd, t_vars *vars)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return ;
	exec_loop(cmd, exec, vars);
	free(exec);
}
