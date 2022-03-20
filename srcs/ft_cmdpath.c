/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:33:40 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/04 14:46:30 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_cmdpath(t_vars *vars, char *cmd)
{
	char	*cmdpath;
	char	*env_path;
	char	**paths;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	env_path = ft_getenv("PATH", vars->envp);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strnjoin(paths[i], "/", 1);
		paths[i] = ft_strnjoin(paths[i], cmd, ft_strlen(cmd));
		if (access(paths[i], X_OK) != 0)
			continue ;
		cmdpath = ft_strdup(paths[i]);
		return (ft_free_2d(paths), cmdpath);
	}
	return (ft_free_2d(paths), NULL);
}
