/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:52:39 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/26 20:12:57 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_cd(char **cmd, char **envp)
{
	char	*home_path;

	if (!cmd[1])
	{
		home_path = ft_getenv("HOME", envp);
		if (!home_path)
			ft_putendl_fd("bash: cd: HOME not set", 2);
		if (chdir(home_path) == -1)
			return (1);
		return (0);
	}
	if (chdir(cmd[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(cmd[1]);
		return (1);
	}
	return (0);
}
