/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:36:04 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/25 12:23:03 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_init_vars(t_vars *vars, char *envp[])
{
	char	**t_envp;

	t_envp = ft_arrdup(envp);
	if (!t_envp)
		return (0);
	vars->envp = ft_env_lstnew(t_envp);
	if (!vars->envp)
		return (ft_free_2d(t_envp), 0);
	vars->last_cmdline = NULL;
	vars->tokens = NULL;
	return (1);
}
