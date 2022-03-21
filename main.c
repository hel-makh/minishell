/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:42:23 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/21 21:18:56 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

		printf("\n#################### Tokenization ###################\n\n");

		ft_tokenization(&vars);
		if (!ft_lstsize(vars.tokens))
			continue ;

		t_list	*t_tokens = vars.tokens;
		while (t_tokens)
		{
			printf("%d - '%s'\n", t_tokens->type, t_tokens->content);
			t_tokens = t_tokens->next;
		}
		
		if (!ft_verify_syntax(&vars))
		{
			ft_putendl_fd("\n>> Syntax error.\n", STDOUT_FILENO);
			continue ;
		}
		
		printf("\n###################### Parsing ######################\n\n");

		if (!ft_parse_cmds(&vars))
			return (ft_free_program(&vars), EXIT_FAILURE);

		int cmd_n = 1;
		t_cmd	*t_cmds = vars.cmds;
		while (t_cmds)
		{
			printf("=====================[ %d ]======================\n", cmd_n++);
			int i = -1;
			while (t_cmds->cmd[++i])
				printf("%d. %s\n", i, t_cmds->cmd[i]);
			printf("type: %d\n", t_cmds->type);
			printf("subsh_lvl: %d\n", t_cmds->subsh_lvl);
			t_list	*t_lists = t_cmds->redirect;
			while (t_lists)
			{
				printf("redirect: %s\n", t_lists->content);
				printf("redirect_type: %d\n", t_lists->type);
				t_lists = t_lists->next;
			}
			t_cmds = t_cmds->next;
		}
		
		printf("\n##################### Expansion #####################\n\n");

		if (!ft_expand_env_vars(&vars))
			return (ft_free_program(&vars), EXIT_FAILURE);

		cmd_n = 1;
		t_cmds = vars.cmds;
		while (t_cmds)
		{
			printf("=====================[ %d ]======================\n", cmd_n++);
			int i = -1;
			while (t_cmds->cmd[++i])
				printf("%d. %s\n", i, t_cmds->cmd[i]);
			printf("type: %d\n", t_cmds->type);
			printf("subsh_lvl: %d\n", t_cmds->subsh_lvl);
			t_list	*t_lists = t_cmds->redirect;
			while (t_lists)
			{
				printf("redirect: %s\n", t_lists->content);
				printf("redirect_type: %d\n", t_lists->type);
				t_lists = t_lists->next;
			}
			t_cmds = t_cmds->next;
		}

		printf("\n");
	}
	ft_free_program(&vars);
	return (EXIT_SUCCESS);
}
