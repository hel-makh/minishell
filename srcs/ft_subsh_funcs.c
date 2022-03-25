/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subsh_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 23:04:41 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/24 23:49:48 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_subsh_levelup(t_env **envp, int level)
{
	t_env	*t_envp;
	char	**t_array;

	if (!envp || !*envp)
		return ;
	while (level > 0)
	{
		if ((*envp)->envp)
		{
			t_array = ft_arrdup((*envp)->envp);
			if (!t_array)
				return ;
		}
		t_envp = ft_env_lstnew(t_array);
		if (!t_envp)
		{
			t_array = ft_free_2d(t_array);
			return ;
		}
		ft_env_lstadd_back(envp, t_envp);
		level --;
	}
}

void	ft_subsh_leveldown(t_env **envp, int level)
{
	t_env	*t_envp;

	if (!envp || !*envp)
		return ;
	while (level > 0)
	{
		t_envp = ft_env_lstlast(*envp);
		t_envp->envp = ft_free_2d(t_envp->envp);
		t_envp = ft_free(t_envp);
		level --;
	}
}
