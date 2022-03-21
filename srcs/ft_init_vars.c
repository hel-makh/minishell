/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:36:04 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/21 17:43:38 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_init_vars(t_vars *vars, char *envp[])
{
	size_t	i;

	vars->envp = ft_calloc(ft_arrlen(envp) + 1, sizeof(char *));
	if (!vars->envp)
		return (0);
	i = 0;
	while (i < ft_arrlen(envp))
	{
		vars->envp[i] = ft_strdup(envp[i]);
		i ++;
	}
	vars->last_cmdline = NULL;
	vars->tokens = NULL;
	return (1);
}
