/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:53:36 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/26 20:12:51 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_echo(char **cmd)
{
	int	option;
	int	i;

	option = 0;
	i = 1;
	while (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
	{
		option = 1;
		i ++;
	}
	while (cmd[i])
	{
		printf ("%s", cmd[i]);
		if (cmd[i + 1])
			printf (" ");
		i ++;
	}
	if (!option)
		printf ("\n");
	return (0);
}
