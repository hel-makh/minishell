/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:36:04 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/20 14:36:53 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_vars(int argc, char *argv[], char *envp[], t_vars *vars)
{
	(void)argc;
	(void)argv;
	vars->envp = envp;
	vars->tokens = NULL;
	// vars->redirect_input = NULL;
	// vars->redirect_output = NULL;
	// vars->redirect_append = NULL;
	// vars->heredoc_delimiter = NULL;
}
