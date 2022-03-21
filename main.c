/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:42:23 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/21 11:10:19 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// int	ft_exec_cmdline(t_vars *vars)
// {
// 	pid_t	pid;
// 	int		i;

// 	vars->pipeline = ft_split_pipes(vars->cmdline);
// 	if (!vars->pipeline)
// 		return (0);
// 	vars->cmd_count = ft_arrlen(vars->pipeline);
// 	i = 0;
// 	while (vars->pipeline[i])
// 	{
// 		if (pipe(vars->p) == -1)
// 			return (perror("pipe"), 0);
// 		pid = fork();
// 		if (pid == -1)
// 			return (perror("fork"), 0);
// 		if (pid == 0)
// 			ft_exec_pipeline(vars, i);
// 		waitpid(pid, NULL, 0);
// 		// char buff[100];
// 		// buff[0] = '\0';
// 		// int ret = read(vars->p[STDIN_FILENO], buff, 100);
// 		// buff[ret] = '\0';
// 		// printf("pipe: '%s'\n", buff);
// 		i ++;
// 	}
// 	return (1);
// }

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	ft_init_vars(argc, argv, envp, &vars);
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, ft_handle_signals);
	vars.cmdline = ft_strdup("");
	while (vars.cmdline)
	{
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
		ft_tokenization(&vars);
		if (!ft_lstsize(vars.tokens))
			continue ;

		t_list	*t_tokens = vars.tokens;
		while (t_tokens)
		{
			printf("%d - '%s'\n", t_tokens->type, t_tokens->content);
			t_tokens = t_tokens->next;
		}
		printf("\n#######################################\n\n");
		
		if (!ft_verify_syntax(&vars))
		{
			ft_putendl_fd("\n>> Syntax error.\n", STDOUT_FILENO);
			continue ;
		}

		if (!ft_parse_cmds(&vars))
			return (ft_free_program(&vars), EXIT_FAILURE);

		t_cmd	*t_cmds = vars.cmds;
		while (t_cmds)
		{
			int i = -1;
			while (t_cmds->cmd[++i])
				printf("%d. %s\n", i, t_cmds->cmd[i]);
			printf("type: %d\n", t_cmds->type);
			printf("subsh_lvl: %d\n", t_cmds->subsh_lvl);
			t_list	*t_lists = vars.cmds->redirect;
			while (t_lists)
			{
				printf("redirection: %s\n", t_lists->content);
				printf("redirection_type: %d\n", t_lists->type);
				t_lists = t_lists->next;
			}
			t_cmds = t_cmds->next;
			printf("=======================================\n");
		}
		
		// if (!ft_exec_cmdline(&vars))
		// 	return (ft_free_program(&vars), EXIT_FAILURE);
		
		ft_lstclear(&vars.tokens);
		ft_cmd_lstclear(&vars.cmds);
	}
	ft_free_program(&vars);
	return (EXIT_SUCCESS);
}
