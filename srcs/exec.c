/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:35:04 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/26 12:40:59 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_path(char **paths, char *cmd)
{
	int		i;
	int		result;

	i = 0;
	while (paths[i])
	{
		paths[i] = ft_stradd(paths[i], "/");
		if (!paths[i])
			return (NULL);
		paths[i] = ft_stradd(paths[i], cmd);
		if (!paths[i])
			return (NULL);
		result = access(paths[i], F_OK);
		if (result == 0)
		{
			result = access(paths[i], X_OK);
			if (result == 0)
				return (ft_strdup(paths[i]));
			else
				exit_cmd_notfound(cmd, 126);
		}
		i++;
	}
	return (NULL);
}

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
