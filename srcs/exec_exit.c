/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:11:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/26 12:49:23 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int arr_size(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int exit_cmd(char **cmd)
{
	int size;

	size = ft_arrlen(cmd);
	
	if (size > 1)
	{
		
	}
}