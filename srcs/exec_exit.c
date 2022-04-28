/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:11:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/04/28 23:26:57 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_numeric(const char *s)
{
	int	is_numeric;
	int	i;

	is_numeric = 0;
	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && ft_isdigit(s[i]))
	{
		is_numeric = 1;
		i ++;
	}
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] != '\0')
		is_numeric = 0;
	return (is_numeric);
}

static double	ft_atoi_exit(const char *str)
{
	int		sign;
	double	nbr;

	sign = 1;
	nbr = 0;
	while (ft_isspace(*str))
		str ++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str ++;
	}
	while (ft_isdigit(*str))
	{
		nbr = (nbr * 10) + (*str - '0');
		str ++;
	}
	return (sign * nbr);
}

int	builtin_exit(char **cmd)
{
	double		exit_status;
	int			size;

	ft_putendl_fd("exit", STDOUT_FILENO);
	size = ft_arrlen(cmd);
	if (size == 1)
		exit(g_glob.exit_status);
	exit_status = ft_atoi_exit(cmd[1]);
	if (!is_numeric(cmd[1]) || exit_status > LONG_MAX || exit_status < LONG_MIN)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
	}
	if (size > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exit(exit_status);
}
