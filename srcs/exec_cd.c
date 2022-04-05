/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:52:39 by ybensell          #+#    #+#             */
/*   Updated: 2022/04/05 13:57:35 by hel-makh         ###   ########.fr       */
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

static int	cd_oldpwd(char *old_cwd, char ***envp)
{
	char	*old_pwd;

	old_pwd = ft_getenv("OLDPWD", *envp);
	if (!old_pwd)
		return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 0);
	if (chdir(old_pwd) == -1)
		return (0);
	if (!change_pwd_env(old_cwd, envp))
		return (0);
	return (1);
}

static int	cd_home(char *old_cwd, char ***envp)
{
	char	*home_path;

	home_path = ft_getenv("HOME", *envp);
	if (!home_path)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 0);
	if (chdir(home_path) == -1)
		return (0);
	if (!change_pwd_env(old_cwd, envp))
		return (0);
	return (1);
}

int	builtin_cd(char **cmd, char ***envp)
{
	char	cwd[4096];

	if (!getcwd(cwd, 4096))
		return (EXIT_FAILURE);
	if (!cmd[1] && !cd_home(cwd, envp))
		return (EXIT_FAILURE);
	if (!*cmd[1])
		return (EXIT_SUCCESS);
	if (!ft_strcmp(cmd[1], "-") && !cd_oldpwd(cwd, envp))
		return (EXIT_FAILURE);
	if (chdir(cmd[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(cmd[1]);
		return (EXIT_FAILURE);
	}
	return (change_pwd_env(cwd, envp));
}
