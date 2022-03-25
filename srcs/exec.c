/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:35:04 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/25 12:47:29 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


int	cmd_nbr(t_cmd **cmd)
{
	int			i;
	t_cmd	*tmp;

	tmp = *cmd;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*find_cmd(t_cmd *cmd)
{
	char	*cmd_temp;
	char	**paths;
	char	*path;

	path = getenv("PATH");  //reminder to search in our own enviroment table
	if (!path)
		exit_perror();
	paths = get_env(path);
	cmd_temp = find_path(paths, cmd->cmd[0]);
	if (!cmd_temp)
	{
		write(2, "minishell: ", 12);
		write(2, cmd->cmd[0], ft_strlen(cmd->cmd[0]));
		write(2, ": not found\n", 13);
		exit(127);
	}
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
	if (access(cmd->cmd[0], F_OK) == 0)
	{
		if (access(cmd->cmd[0], X_OK) == 0)
			tmp = cmd->cmd[0];
	}
	else
		tmp = find_cmd(cmd);
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
