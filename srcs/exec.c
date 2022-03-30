/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:35:04 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/30 21:08:56 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_path(char **paths, char *cmd)
{
	int			i;
	int			result;
	struct stat	path_stat;

	i = 0;
	while (paths[i])
	{
		paths[i] = ft_stradd(paths[i], "/");
		if (!paths[i])
			return (NULL);
		paths[i] = ft_stradd(paths[i], cmd);
		if (!paths[i])
			return (NULL);
		lstat(paths[i], &path_stat);
		if (S_ISREG(path_stat.st_mode))
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
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->cmd[0], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		exit(127);
	}
	paths = ft_split(path, ':');
	if (!paths)
		exit_perror();
	cmd_temp = find_path(paths, cmd->cmd[0]);
	paths = ft_free_2d(paths);
	if (!cmd_temp)
		exit_cmd_notfound(cmd->cmd[0], 127);
	return (cmd_temp);
}

void	expand_args(t_cmd **cmd, t_vars *vars)
{
	t_cmd	*t_cmd;
	t_list	*redirect;
	int		i;

	t_cmd = *cmd;
	i = 0;
	while (t_cmd->cmd[i])
	{
		ft_expand_env_vars(vars->envp, &t_cmd->cmd[i]);
		if (!ft_expand_wildcards(cmd, NULL, &i))
			t_cmd->cmd[i] = ft_remove_quotes(t_cmd->cmd[i]);
		i ++;
	}
	redirect = t_cmd->redirect;
	while (redirect)
	{
		ft_expand_env_vars(vars->envp, &redirect->content);
		if (!ft_expand_wildcards(NULL, &redirect, NULL))
			redirect->content = ft_remove_quotes(redirect->content);
		redirect = redirect->next;
	}
}

void	the_execution(t_cmd *cmd, t_vars *vars)
{
	char	*tmp;

	if (!cmd->cmd[0])
	{
		g_glob.exit_status = 0;
		return ;
	}
	expand_args(&cmd, vars);
	if (is_built_in(cmd->cmd[0]))
	{
		g_glob.exit_status = exec_built_in(cmd->cmd, vars);
		if ((cmd->next && cmd->next->type == PIPE)
			|| cmd->type == PIPE)
			exit (g_glob.exit_status);
		return ;
	}
	if (access(cmd->cmd[0], F_OK) == 0
		&& access(cmd->cmd[0], X_OK) == 0)
		tmp = cmd->cmd[0];
	else
		tmp = find_cmd(cmd, vars);
	if ((execve(tmp, cmd->cmd, vars->envp) == -1))
		exit_perror();
}
