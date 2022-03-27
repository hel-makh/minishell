/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:13:32 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/27 21:52:04 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// #include "Libft/ft_isalpha.c"
// #include "Libft/ft_isdigit.c"
// #include "Libft/ft_isalnum.c"
// #include "Libft/ft_strlen.c"
// #include "Libft/ft_strcpy.c"
// #include "Libft/ft_strcat.c"
// #include "Libft/ft_strchr.c"
// #include "Libft/ft_strrchr.c"
// #include "Libft/ft_bzero.c"
// #include "Libft/ft_calloc.c"
// #include "Libft/ft_strdup.c"
// #include "Libft/ft_arrdup.c"
// #include "Libft/ft_strnstr.c"
// #include "Libft/ft_substr.c"
// #include "Libft/ft_putchar_fd.c"
// #include "Libft/ft_putstr_fd.c"
// #include "Libft/ft_putendl_fd.c"
// #include "Libft/ft_strcmp.c"
// #include "Libft/ft_strncmp.c"
// #include "Libft/ft_free.c"
// #include "Libft/ft_stradd.c"
// #include "Libft/ft_joinstrs.c"
// #include "Libft/ft_arrlen.c"
// #include "Libft/ft_add_str2arr.c"
// #include "Libft/ft_replace_str.c"
// #include "Libft/ft_replace_arr.c"
// #include "Libft/ft_split.c"

// #include "srcs/ft_wc_strcmp.c"
// #include "srcs/ft_remove_quotes.c"
// #include "srcs/ft_lstfuncs.c"
// #include "srcs/ft_cmd_lstfuncs.c"
// #include "srcs/ft_getenv.c"
// #include "srcs/ft_init_vars.c"
// #include "srcs/ft_handle_signals.c"
// #include "srcs/ft_tokenization.c"
// #include "srcs/ft_verify_syntax.c"
// #include "srcs/ft_parse_cmds.c"
// #include "srcs/ft_expand_env_vars.c"
// #include "srcs/ft_expand_wildcards.c"
// #include "srcs/exec.c"
// #include "srcs/exec_cmds.c"
// #include "srcs/exec_redirections.c"
// #include "srcs/exec_tools.c"
// #include "srcs/exec_heredoc.c"
// #include "srcs/exec_pipes.c"
// #include "srcs/exec_builtin.c"
// #include "srcs/exec_cd.c"
// #include "srcs/exec_pwd.c"
// #include "srcs/exec_echo.c"
// #include "srcs/exec_env.c"
// #include "srcs/exec_unset.c"
// #include "srcs/exec_exit.c"
// #include "srcs/ft_free_program.c"

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	if (!ft_init_vars(&vars, envp))
		return (EXIT_FAILURE);
	signal(SIGINT, ft_handle_signals);
	// signal(SIGQUIT, ft_handle_signals);
	vars.cmdline = ft_strdup("");
	while (vars.cmdline)
	{
		ft_lstclear(&vars.tokens);
		ft_cmd_lstclear(&vars.cmds);
		vars.cmdline = ft_free(vars.cmdline);
		vars.cmdline = readline(PROMPT);
		// vars.cmdline = ft_strdup("echo hh > 123*");
		if (!vars.cmdline)
			break ;
		if (*vars.cmdline && (!vars.last_cmdline || (vars.last_cmdline
					&& ft_strcmp(vars.cmdline, vars.last_cmdline))))
		{
			vars.last_cmdline = ft_free(vars.last_cmdline);
			vars.last_cmdline = ft_strdup(vars.cmdline);
			add_history(vars.cmdline);
		}
		if (!ft_tokenization(&vars) || !ft_lstsize(vars.tokens))
			continue ;
		if (!ft_verify_syntax(&vars))
		{
			ft_putendl_fd("\n>> Syntax error.\n", STDOUT_FILENO);
			continue ;
		}
		if (!ft_parse_cmds(&vars))
			continue ;
		execute_cmds(&vars);
	}
	ft_free_program(&vars);
	return (EXIT_SUCCESS);
}
