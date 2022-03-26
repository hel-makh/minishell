/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:33:18 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/26 21:35:00 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i ++;
	}
	return (1);
}
