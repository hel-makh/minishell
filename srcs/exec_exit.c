/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:11:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/30 17:59:25 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_numb(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == '\f')
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == '\f')
		i++;
	return (s[i] == '\0');
}

static double	ft_atoi_exit(const char *str)
{
	int		sign;
	double	nbr;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\r' || *str == '\f')
		str ++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str ++;
	}
	while (*str >= '0' && *str <= '9')
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
		if (!is_numb(cmd[1]) || ret > LONG_MAX || ret < LONG_MIN)
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
