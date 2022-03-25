/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:16:11 by mbabela           #+#    #+#             */
/*   Updated: 2022/03/24 17:40:00 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd_cmd(void)
{
	char	buff[4096];

	if (getcwd(buff, 4096))
	{
		printf ("%s\n", buff);
		exit_status = 0;
		return (0);
	}
	else
	{
		perror ("minishell");
		return (1);
	}
}
