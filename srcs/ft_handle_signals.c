/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 08:35:27 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/30 18:57:36 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_process(int sign)
{
	if (sign == SIGQUIT && g_glob.pid == 0)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_glob.exit_status = 131;
	}
	else if (sign == SIGINT && g_glob.pid == 0)
	{
		ft_putchar_fd('\n', 1);
		g_glob.exit_status = 130;
	}
}

static void	signal_heredoc(int sign)
{
	if (sign == SIGINT)
	{
		g_glob.heredoc = 0;
		ft_putchar_fd('\n', 1);
		rl_redisplay();
	}
}

void	signals_handler(int sign)
{
	if (g_glob.heredoc)
		signal_heredoc(sign);
	else
	{
		g_glob.exit_status = 1;
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
