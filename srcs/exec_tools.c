/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:34:52 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/24 16:52:59 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_perror(void)
{
	perror ("Error");
	exit (1);
}

char	**get_env(char *env)
{
	char	**paths;

	paths = exec_split(env, ':');
	if (!(paths))
		return (NULL);
	return (paths);
}

char	*find_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	int		result;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd);
		if (!paths)
			return (NULL);
		result = access(path, F_OK);
		if (result == 0)
			return (path);
		free (path);
		i++;
	}
	return (NULL);
}
