/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:34:52 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/25 16:09:21 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_perror(void)
{
	perror ("Error");
	exit (1);
}

void	exit_cmd_notfound(char *cmd, int exit_status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (exit_status == 126)
		ft_putendl_fd(": Permission denied", 2);
	else if (exit_status == 127)
		ft_putendl_fd(": command not found", 2);
	exit(exit_status);
}

char	*find_path(char **paths, char *cmd)
{
	int		i;
	int		result;

	i = 0;
	while (paths[i])
	{
		paths[i] = ft_stradd(paths[i], "/");
		if (!paths[i])
			return (NULL);
		paths[i] = ft_stradd(paths[i], cmd);
		if (!paths[i])
			return (NULL);
		result = access(paths[i], F_OK);
		if (result == 0)
		{
			result = access(paths[i], X_OK);
			if (result == 0)
				return (ft_strdup(paths[i]));
			else
				exit_cmd_notfound(cmd, 126);
		}
		i++;
	}
	return (NULL);
}
