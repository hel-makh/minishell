/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:11:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/26 15:14:28 by ybensell         ###   ########.fr       */
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

static long long	ft_atoi_exit(const char *str)
{
	int	sign;
	int	nbr;

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

int exit_cmd(char **cmd)
{
	long long	ret;
	int		size;

	size = ft_arrlen(cmd);
	if (size == 1)
	{
		ft_putendl_fd("exit",1);
		exit(0);
	}
	if (size == 2)
	{
		ret = ft_atoi_exit(cmd[1]);
		if (!is_numb(cmd[1]) || ret > 9223372036854775807 || ret < -9223372036854775800)
		{
			ft_putstr_fd("minishell: exit: ",2);
			ft_putstr_fd(cmd[1],2);
			ft_putendl_fd(" numeric argument required",2);
			exit(255);
		}
		else
			exit((unsigned char)ret);
	}
	else
	{
		ft_putendl_fd("exit",1);
		ft_putendl_fd("minishell: exit: too many arguments",2);
		return (1);
	}	
}
