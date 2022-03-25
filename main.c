/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:42:23 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/25 12:45:04 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// #include "Libft/ft_isalpha.c"
// #include "Libft/ft_isdigit.c"
// #include "Libft/ft_isalnum.c"
// #include "Libft/ft_strlen.c"
// #include "Libft/ft_strchr.c"
// #include "Libft/ft_strrchr.c"
// #include "Libft/ft_bzero.c"
// #include "Libft/ft_calloc.c"
// #include "Libft/ft_strdup.c"
// #include "Libft/ft_strnstr.c"
// #include "Libft/ft_substr.c"
// #include "Libft/ft_putendl_fd.c"
// #include "Libft/ft_strcmp.c"
// #include "Libft/ft_free.c"
// #include "Libft/ft_arrlen.c"
// #include "Libft/ft_add_str2arr.c"
// #include "Libft/ft_replace_str.c"
// #include "Libft/ft_replace_arr.c"

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
// #include "srcs/ft_free_program.c"

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	if (!ft_init_vars(&vars, envp))
		return (EXIT_FAILURE);
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, ft_handle_signals);
	vars.cmdline = ft_strdup("");
	while (vars.cmdline)
	{
		ft_lstclear(&vars.tokens);
		ft_cmd_lstclear(&vars.cmds);
		vars.cmdline = ft_free(vars.cmdline);
		vars.cmdline = readline(PROMPT);
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

		execute_cmd(vars.cmds,&vars);
	}
	ft_free_program(&vars);
	return (EXIT_SUCCESS);
}
