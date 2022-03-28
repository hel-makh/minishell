/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:17:43 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/28 19:18:04 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export(char **envp)
{
	size_t	cmp;
	size_t	arr_len;
	size_t	i;
	size_t	j;

	arr_len = ft_arrlen(envp);
	i = 0;
	while (i < arr_len)
	{
		j = 0;
		while (!envp[j])
			j ++;
		cmp = j;
		while (j < arr_len)
		{
			if (envp[j] && envp[cmp]
				&& ft_strcmp(envp[j], envp[cmp]) < 0)
				cmp = j;
			j ++;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(envp[cmp], STDOUT_FILENO);
		envp[cmp] = NULL;
		i ++;
	}
}
