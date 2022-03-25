/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:11:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/25 10:25:18 by ybensell         ###   ########.fr       */
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

	size = arr_size(cmd);
	
	if (size > 1)
	{
		
	}
}