/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:16:11 by mbabela           #+#    #+#             */
/*   Updated: 2022/03/26 13:14:15 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd_cmd(void)
{
	char	buff[4096];

	if (getcwd(buff, 4096))
	{
		printf ("%s\n", buff);
		// exit_status = 0;
		return (0);
	}
	else
	{
		perror ("minishell");
		return (1);
	}
}
