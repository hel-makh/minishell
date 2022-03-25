/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:53:36 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/24 17:34:32 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	echo_builtin(char **cmd)
{
	int	i;

	if (cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
	{
		i = 1;
		while (cmd[++i])
		{
			printf ("%s", cmd[i]);
			if (i < get_size(cmd) - 1)
				printf (" ");
		}
	}
	else
	{
		i = 0;
		while (cmd[++i])
		{
			printf ("%s", cmd[i]);
			if (i < get_size(cmd) - 1)
				printf (" ");
		}
		printf ("\n");
	}
	return (0);
}
