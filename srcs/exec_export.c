/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 22:30:08 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/28 16:06:47 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_export(char **envp)
{
	size_t	cmp;
	size_t	arr_len;
	size_t	i;
	size_t	j;

	arr_len = ft_arrlen(envp);
	i = 0;
	while (i < arr_len)
	{
		j = 0;
		while (!envp[j])
			j ++;
		cmp = j;
		while (j < arr_len)
		{
			if (envp[j] && envp[cmp]
				&& ft_strcmp(envp[j], envp[cmp]) < 0)
				cmp = j;
			j ++;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(envp[cmp], STDOUT_FILENO);
		envp[cmp] = NULL;
		i ++;
	}
}

static int	ft_varname_len_export(char *var_name)
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
			(*envp)[i] = ft_free((*envp)[i]);
			(*envp)[i] = ft_strdup(var);
			if (!(*envp)[i])
				return (0);
		}
		i ++;
	}
	return (1);
}

int	builtin_export(char **cmd, char ***envp)
{
	int		i;
	char	*var_name;

	if (!cmd[1])
		return (print_export(*envp), EXIT_SUCCESS);
	i = 1;
	while (cmd[i])
	{
		if (ft_is_varname(cmd[i]))
		{
			var_name = ft_substr(cmd[i], 0, ft_varname_len_export(cmd[i]));
			if (!var_name)
				return (EXIT_FAILURE);
			if (!ft_getenv(var_name, *envp))
			{
				*envp = ft_add_str2arr(*envp, cmd[i]);
				if (!*envp)
					return (EXIT_FAILURE);
			}
			else if (!ft_change_env_var(envp, cmd[i]))
				return (EXIT_FAILURE);
		}
		i ++;
	}
	return (EXIT_SUCCESS);
}
