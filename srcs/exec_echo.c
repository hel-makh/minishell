/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:53:36 by ybensell          #+#    #+#             */
/*   Updated: 2022/04/05 14:22:20 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_echo_newline(char *cmd)
{
	int	i;

	if (ft_strncmp(cmd, "-n", 2))
		return (0);
	i = 2;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i ++;
	}
	return (1);
}

int	builtin_echo(char **cmd)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (cmd[i] && is_echo_newline(cmd[i]))
	{
		newline = 0;
		i ++;
	}
	while (cmd[i])
	{
		printf ("%s", cmd[i]);
		if (cmd[i + 1])
			printf (" ");
		i ++;
	}
	if (newline)
		printf ("\n");
	return (EXIT_SUCCESS);
}
