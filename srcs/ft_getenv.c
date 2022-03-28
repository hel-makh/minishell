/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:41:48 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/28 13:09:47 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *var, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var))
			&& envp[i][ft_strlen(var)] == '=')
			return (&envp[i][ft_strlen(var) + 1]);
		i ++;
	}
	return (NULL);
}
