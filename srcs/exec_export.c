/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 22:30:08 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/28 12:43:15 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	print_export(char **envp)
// {

// }

static int	ft_is_varname(char *var_name)
{
	int	alpha;
	int	invalid;
	int	i;

	alpha = 0;
	invalid = 0;
	i = 0;
	while (var_name[i] && var_name[i] != '=')
	{
		if (ft_isalpha(var_name[i]))
			alpha ++;
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			invalid = 1;
		i ++;
	}
	if (!alpha || invalid)
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(var_name, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	builtin_export(char **cmd, char ***envp)
{
	int	i;

	// if (!cmd[1])
	// 	return (print_export(envp), 1);
	if (!cmd[1])
		return (builtin_env(*envp));
	i = 1;
	while (cmd[i])
	{
		if (ft_is_varname(cmd[i]))
			*envp = ft_add_str2arr(*envp, cmd[i]);
		i ++;
	}
	return (EXIT_SUCCESS);
}