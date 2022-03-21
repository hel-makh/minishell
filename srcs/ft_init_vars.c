/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:36:04 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/21 16:45:55 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_init_vars(int argc, char *argv[], char *envp[], t_vars *vars)
{
	(void)argc;
	(void)argv;
	vars->envp = ft_calloc(ft_arrlen(envp), sizeof(char *));
	if (!vars->envp)
		return (0);
	ft_memmove(vars->envp, envp, ft_arrlen(envp) * sizeof(char *));
	vars->last_cmdline = NULL;
	vars->tokens = NULL;
	return (1);
}
