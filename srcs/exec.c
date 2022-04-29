/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:35:04 by ybensell          #+#    #+#             */
/*   Updated: 2022/04/29 00:08:29 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_path(char **paths, char *cmd)
{
	int			i;
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
		if (S_ISREG(path_stat.st_mode) && access(paths[i], F_OK) == 0)
		{
			if (access(paths[i], X_OK) == 0)
				return (ft_strdup(paths[i]));
			exit_error(cmd, "Permission denied", 126);
		}
		i++;
	}
	return (NULL);
}

static char	*find_cmd(t_cmd *cmd, t_vars *vars)
{
	struct stat	path_stat;
	char		*cmd_temp;
	char		*path;
	char		**paths;

	lstat(cmd->cmd[0], &path_stat);
	if (S_ISREG(path_stat.st_mode) && access(cmd->cmd[0], F_OK) == 0)
	{
		if (access(cmd->cmd[0], X_OK) == 0)
			return (cmd->cmd[0]);
		exit_error(cmd->cmd[0], "Permission denied", 126);
	}
	path = ft_getenv("PATH", vars->envp);
	if (!path)
		exit_error(cmd->cmd[0], "No such file or directory", 127);
	paths = ft_split(path, ':');
	if (!paths)
		exit (1);
	cmd_temp = find_path(paths, cmd->cmd[0]);
	paths = ft_free_2d(paths);
	if (!cmd_temp)
		exit_error(cmd->cmd[0], "command not found", 127);
	return (cmd_temp);
}

static int	split_args(t_cmd **cmd, int *index)
{
	char	**split;
	size_t	i;

	split = ft_split_args((*cmd)->cmd[*index]);
	if (!split)
		return (0);
	(*cmd)->cmd = ft_replace_arr((*cmd)->cmd, split, *index, 1);
	if (!(*cmd)->cmd)
		return (ft_free_2d(split), 0);
	i = 0;
	while (i < ft_arrlen(split))
	{
		if (!ft_expand_wildcards(cmd, NULL, index))
			(*cmd)->cmd[*index] = ft_remove_quotes((*cmd)->cmd[*index]);
		i ++;
		*index += 1;
	}
	*index -= 1;
	split = ft_free_2d(split);
	return (1);
}

static void	expand_args(t_cmd **cmd, t_vars *vars)
{
	t_cmd	*t_cmd;
	t_list	*redirect;
	int		i;

	t_cmd = *cmd;
	i = 0;
	while (t_cmd->cmd[i])
	{
		ft_expand_env_vars(vars->envp, &t_cmd->cmd[i]);
		if (!split_args(&t_cmd, &i))
			return ;
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
	char		*tmp;

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
	tmp = find_cmd(cmd, vars);
	if ((execve(tmp, cmd->cmd, vars->envp) == -1))
		exit_perror("minishell: execve");
}
