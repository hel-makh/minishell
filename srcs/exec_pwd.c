/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:16:11 by ybensell          #+#    #+#             */
/*   Updated: 2022/04/05 23:25:12 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_pwd(void)
{
	char	cwd[4096];

	getcwd(cwd, 4096);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
