/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:36:04 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/30 10:41:20 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	shlvl[0] = ft_strdup("");
	shlvl[1] = ft_strjoin("SHLVL=", shlvl_new_value);
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
	return (1);
}
