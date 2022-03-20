/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:52:56 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/20 14:57:27 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_program(t_vars *vars)
{
	vars->cmdline = ft_free(vars->cmdline);
	vars->last_cmdline = ft_free(vars->last_cmdline);
	// vars->pipeline = ft_free_2d(vars->pipeline);
}
