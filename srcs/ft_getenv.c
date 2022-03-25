/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:41:48 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/25 12:11:57 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *var, t_env *envp)
{
	char	**env_arr;
	int		i;

	env_arr = ft_env_lstlast(envp)->envp;
	i = 0;
	while (env_arr[i])
	{
		if (ft_strnstr(env_arr[i], var, ft_strlen(env_arr[i]))
			&& env_arr[i][ft_strlen(var)] == '=')
			return (&env_arr[i][ft_strlen(var) + 1]);
		i ++;
	}
	return (NULL);
}
