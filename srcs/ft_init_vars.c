/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:36:04 by hel-makh          #+#    #+#             */
/*   Updated: 2022/04/26 02:05:58 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_set_pwd(t_vars *vars)
{
	char	**pwd;
	char	cwd[4096];

	pwd = ft_calloc(3, sizeof(char *));
	if (!pwd)
		return (0);
	if (!getcwd(cwd, 4096) && errno == ENOENT)
		perror("minishell-init: error retrieving current directory: "
			"getcwd: cannot access parent directories");
	pwd[0] = ft_strdup("");
	if (!pwd[0])
		return (ft_free_2d(pwd), 0);
	pwd[1] = ft_strjoin("PWD=", cwd);
	if (!pwd[1])
		return (ft_free_2d(pwd), 0);
	builtin_export(pwd, &vars->envp);
	pwd = ft_free_2d(pwd);
	return (1);
}

static int	ft_unset_oldpwd(t_vars *vars)
{
	char	**unset;

	unset = ft_calloc(3, sizeof(char *));
	if (!unset)
		return (0);
	unset[0] = ft_strdup("");
	if (!unset[0])
		return (ft_free_2d(unset), 0);
	unset[1] = ft_strdup("OLDPWD");
	if (!unset[1])
		return (ft_free_2d(unset), 0);
	if (builtin_unset(unset, &vars->envp) == EXIT_FAILURE)
		return (ft_free_2d(unset), 0);
	return (ft_free_2d(unset), 1);
}

static int	ft_increment_shlvl(t_vars *vars)
{
	char	**shlvl;
	char	*shlvl_value;
	char	*shlvl_new_value;

	shlvl = ft_calloc(3, sizeof(char *));
	if (!shlvl)
		return (0);
	shlvl_value = ft_getenv("SHLVL", vars->envp);
	if (shlvl_value)
		shlvl_new_value = ft_itoa(ft_atoi(shlvl_value) + 1);
	else
		shlvl_new_value = ft_strdup("1");
	if (!shlvl_new_value)
		return (ft_free(shlvl), 0);
	shlvl[0] = ft_strdup("");
	if (!shlvl[0])
		return (ft_free_2d(shlvl), 0);
	shlvl[1] = ft_strjoin("SHLVL=", shlvl_new_value);
	if (!shlvl[1])
		return (ft_free_2d(shlvl), 0);
	shlvl_new_value = ft_free(shlvl_new_value);
	if (builtin_export(shlvl, &vars->envp) == EXIT_FAILURE)
		return (ft_free_2d(shlvl), 0);
	return (ft_free_2d(shlvl), 1);
}

int	ft_init_vars(t_vars *vars, char *envp[])
{
	vars->cmdline = NULL;
	vars->last_cmdline = NULL;
	vars->tokens = NULL;
	vars->cmds = NULL;
	vars->envp = ft_arrdup(envp);
	if (!vars->envp)
		return (0);
	if (!ft_increment_shlvl(vars))
		return (0);
	if (!ft_set_pwd(vars))
		return (0);
	if (!ft_unset_oldpwd(vars))
		return (0);
	return (1);
}
