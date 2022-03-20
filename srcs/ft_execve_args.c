/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:33:29 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/04 14:44:53 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_execve_args(t_vars *vars, char *cmd)
{
	char	**cmd_args;
	char	*cmd_name;

	cmd_args = ft_split_args(cmd);
	if (access(cmd_args[0], X_OK) != 0)
	{
		cmd_name = ft_cmdpath(vars, cmd_args[0]);
		if (!cmd_name)
		{
			printf("minishell: %s: command not found\n", cmd_args[0]);
			ft_free_2d(cmd_args);
			return (NULL);
		}
		cmd_args[0] = ft_free(cmd_args[0]);
		cmd_args[0] = cmd_name;
	}
	return (cmd_args);
}
