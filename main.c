/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:13:32 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/31 12:12:46 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	ft_loop_cmds(t_vars *vars)
{
	g_glob.heredoc = 0;
	ft_lstclear(&vars->tokens);
	ft_cmd_lstclear(&vars->cmds);
	vars->cmdline = ft_free(vars->cmdline);
	vars->cmdline = readline(PROMPT);
	if (!vars->cmdline)
		return (0);
	if (vars->cmdline[0] && (!vars->last_cmdline || (vars->last_cmdline
				&& ft_strcmp(vars->cmdline, vars->last_cmdline))))
	{
		vars->last_cmdline = ft_free(vars->last_cmdline);
		vars->last_cmdline = ft_strdup(vars->cmdline);
		add_history(vars->cmdline);
	}
	if (!ft_tokenization(vars) || !ft_lstsize(vars->tokens))
		return (1);
	if (!ft_verify_syntax(vars))
	{
		ft_putendl_fd("minishell: syntax error.", STDERR_FILENO);
		return (1);
	}
	if (!ft_parse_cmds(vars))
		return (1);
	execute_cmds(vars);
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	if (!ft_init_vars(&vars, envp))
		return (EXIT_FAILURE);
	vars.sa.sa_handler = signals_handler;
	vars.sa.sa_flags = 0;
	sigaction(SIGINT, &vars.sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	vars.cmdline = ft_strdup("");
	while (ft_loop_cmds(&vars))
		;
	ft_free_program(&vars);
	ft_putendl_fd("exit", STDOUT_FILENO);
	return (g_glob.exit_status);
}
