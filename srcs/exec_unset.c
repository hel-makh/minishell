/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:08:18 by hel-makh          #+#    #+#             */
/*   Updated: 2022/04/05 14:26:43 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_varname_unset(char *var_name)
{
	int	invalid;
	int	i;

	invalid = 0;
	i = 0;
	while (var_name[i] && var_name[i] != '='
		&& (var_name[i] != '+' || var_name[i + 1] != '='))
	{
		if (i == 0 && !ft_isalpha(var_name[i]) && var_name[i] != '_')
			invalid = 1;
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			invalid = 1;
		i ++;
	}
	if (invalid)
	{
		ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
		ft_putstr_fd(var_name, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	builtin_unset(char **cmd, char ***envp)
{
	char	**empty_arr;
	int		i;
	int		j;

	empty_arr = ft_calloc (1, sizeof(char *));
	if (!empty_arr)
		return (EXIT_FAILURE);
	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (ft_is_varname_unset(cmd[i]) && (*envp)[j])
		{
			if (!ft_strncmp((*envp)[j], cmd[i], ft_strlen(cmd[i]))
				&& (*envp)[j][ft_strlen(cmd[i])] == '=')
			{
				*envp = ft_replace_arr(*envp, empty_arr, j, 1);
				break ;
			}
			j ++;
		}
		i ++;
	}
	empty_arr = ft_free_2d(empty_arr);
	return (EXIT_SUCCESS);
}
