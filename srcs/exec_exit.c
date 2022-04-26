/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:11:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/04/26 01:54:21 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_numeric(const char *s)
{
	int	i;
	int	is_numeric;

	i = 0;
	is_numeric = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && ft_isdigit(s[i++]))
		is_numeric = 1;
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
	double		ret;
	int			size;

	ft_putendl_fd("exit", STDOUT_FILENO);
	size = ft_arrlen(cmd);
	if (size == 1)
		exit(g_glob.exit_status);
	if (size == 2)
	{
		ret = ft_atoi_exit(cmd[1]);
		if (!is_numeric(cmd[1]) || ret > LONG_MAX || ret < LONG_MIN)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit(255);
		}
		else
			exit((unsigned char)ret);
	}
	else
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
}
