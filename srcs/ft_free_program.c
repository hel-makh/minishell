/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:52:56 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/19 12:48:02 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_program(t_vars *vars)
{
	if (vars->cmdline)
		vars->cmdline = ft_free(vars->cmdline);
	// if (vars->pipeline)
	// 	vars->pipeline = ft_free_2d(vars->pipeline);
}
