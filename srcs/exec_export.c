/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 22:30:08 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/30 23:24:59 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_varname_len_export(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			break ;
		i ++;
	}
	return (i);
}

static int	ft_is_varname(char *var_name)
{
	int	alpha;
	int	invalid;
	int	i;

	alpha = 0;
	invalid = 0;
	i = 0;
	while (var_name[i] && var_name[i] != '='
		&& (var_name[i] != '+' || var_name[i + 1] != '='))
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
		return (0);
	}
	return (1);
}

static int	ft_change_env_var(char ***envp, char *var)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], var, ft_varname_len_export(var)))
		{
			if (var[ft_varname_len_export(var)] == '+'
				&& var[ft_varname_len_export(var) + 1] == '=')
				(*envp)[i] = ft_stradd((*envp)[i], &ft_strchr(var, '=')[1]);
			else if (ft_strlen((*envp)[i]) == ft_varname_len_export(var))
				(*envp)[i] = ft_stradd((*envp)[i], ft_strchr(var, '='));
			else
			{
				(*envp)[i] = ft_free((*envp)[i]);
				(*envp)[i] = ft_strdup(var);
			}
			if (!(*envp)[i])
				return (0);
		}
		i ++;
	}
	return (1);
}

static int	edit_env(char ***envp, char *argv)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_substr(argv, 0, ft_varname_len_export(argv));
	if (!var_name)
		return (0);
	var_value = ft_getenv(var_name, *envp);
	if (var_value && !ft_strchr(argv, '='))
		return (ft_free(var_name), 1);
	if (!var_value && !ft_arr_has_str(*envp, var_name))
	{
		*envp = ft_add_str2arr(*envp, argv);
		if (!*envp)
			return (ft_free(var_name), 0);
	}
	else
	{
		if (!ft_change_env_var(envp, argv))
			return (ft_free(var_name), 0);
	}
	return (ft_free(var_name), 1);
}

int	builtin_export(char **cmd, char ***envp)
{
	char	**temp_envp;
	int		i;

	if (!cmd[1])
	{
		temp_envp = ft_arrdup(*envp);
		if (!temp_envp)
			return (EXIT_FAILURE);
		print_export(temp_envp);
		temp_envp = ft_free(temp_envp);
		return (EXIT_SUCCESS);
	}
	i = 1;
	while (cmd[i])
	{
		if (ft_is_varname(cmd[i]))
		{
			if (!edit_env(envp, cmd[i]))
				return (EXIT_FAILURE);
		}
		i ++;
	}
	return (EXIT_SUCCESS);
}
