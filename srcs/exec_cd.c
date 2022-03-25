/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:52:39 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/25 09:14:45 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_build(char **cmd)
{
	char	*home_path;

	if (cmd[1] == NULL)
	{
		home_path = getenv("HOME");
		if (home_path == NULL)
			write(2, " cd Error !\n", 12);
		return (chdir(home_path) != 0);
	}
	else
	{
		if (chdir(cmd[1]) == 0)
			return (0);
		else
		{
			write(2, cmd[1], ft_strlen(cmd[1]));
			write(2," : No such file or directory \n",30);
			return (1);
		}
	}
}
