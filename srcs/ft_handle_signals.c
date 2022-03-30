/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 08:35:27 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/30 09:45:54 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_process(int sign)
{
	if (kill(g_glob.pid, sign) == 0)
	{
		if (sign == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_glob.exit_status = 131;
		}
		else if (sign == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			rl_redisplay();
			g_glob.exit_status = 130;
		}
	}
}
void signal_heredoc(int sign)
{
	if (g_glob.pid != 0 && sign == SIGINT)
	{
		kill(g_glob.pid, SIGKILL);
		g_glob.exit_status = 130;
	}
	else if (sign == SIGINT)
	{
		g_glob.exit_status = 1;
		ft_putchar_fd('\n', 1);
		rl_redisplay();
	}
}

void	signals_handler(int sign)
{
	if (g_glob.flag == 0)
	{
		if ((sign == SIGINT ) && g_glob.heredoc == 1)
			 signal_heredoc(sign);
		else if ((sign == SIGINT || sign == SIGQUIT) 
				&& g_glob.pid != 0 && g_glob.heredoc == 0)
			signal_process(sign);
		else
		{
			if (sign == SIGINT)
			{
				g_glob.exit_status = 1;
				ft_putchar_fd('\n', 1);
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
			}
		}
	}
}
