/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:52:39 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/28 17:21:31 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	change_pwd_env(char *old_cwd, char ***envp)
{
	char	**pwd;
	char	**old_pwd;
	char	cwd[4096];

	pwd = ft_calloc(3, sizeof(char *));
	if (!pwd)
		return (EXIT_FAILURE);
	if (!getcwd(cwd, 4096))
		return (EXIT_FAILURE);
	pwd[0] = ft_strdup("");
	pwd[1] = ft_strjoin("PWD=", cwd);
	builtin_export(pwd, envp);
	pwd = ft_free_2d(pwd);
	old_pwd = ft_calloc(3, sizeof(char *));
	if (!old_pwd)
		return (EXIT_FAILURE);
	old_pwd[0] = ft_strdup("");
	old_pwd[1] = ft_strjoin("OLDPWD=", old_cwd);
	builtin_export(old_pwd, envp);
	old_pwd = ft_free_2d(old_pwd);
	return (EXIT_SUCCESS);
}

int	builtin_cd(char **cmd, char ***envp)
{
	char	*home_path;
	char	cwd[4096];

	if (!getcwd(cwd, 4096))
		return (EXIT_FAILURE);
	if (!cmd[1])
	{
		home_path = ft_getenv("HOME", *envp);
		if (!home_path)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2),
				EXIT_FAILURE);
		if (chdir(home_path) == -1)
			return (EXIT_FAILURE);
		return (change_pwd_env(cwd, envp));
	}
	if (!*cmd[1])
		return (EXIT_SUCCESS);
	if (chdir(cmd[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(cmd[1]);
		return (EXIT_FAILURE);
	}
	return (change_pwd_env(cwd, envp));
}
