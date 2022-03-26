/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:52:39 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/26 14:03:13 by hel-makh         ###   ########.fr       */
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
			ft_putendl_fd(" cd Error !", 2);
		return (chdir(home_path) != 0);
	}
	else
	{
		if (chdir(cmd[1]) == 0)
			return (0);
		else
		{
			ft_putstr_fd(cmd[1], 2);
			ft_putendl_fd(" : No such file or directory", 2);
			return (1);
		}
	}
}
