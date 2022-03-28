/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:47:56 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/28 10:27:09 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_char_count(char *str, char c)
{
	char	quote;
	int		count;
	int		i;

	quote = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (!quote
			&& (str[i] == '\'' || str[i] == '"')
			&& ft_strchr(&str[i + 1], str[i]))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		if (!quote && str[i] == c)
			count ++;
		i ++;
	}
	return (count);
}

static int	expand_redirect(t_list *redirect, t_vars *vars)
{
	char	*content;

	content = ft_strdup(redirect->content);
	ft_expand_env_vars(vars->envp, &redirect->content);
	if (!ft_expand_wildcards(NULL, &redirect, NULL))
		redirect->content = ft_remove_quotes(redirect->content);
	if (ft_char_count(redirect->content, ' '))
	{
		g_glob.exit_status = 1;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(content, STDERR_FILENO);
		ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
		content = ft_free(content);
		return (0);
	}
	content = ft_free(content);
	return (1);
}

static void	open_redirect_fd(t_list *redirect, t_vars *vars, int *fd)
{
	if (redirect->type == RED_OUT)
		fd[STDOUT_FILENO] = open(redirect->content,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (redirect->type == D_RED_OUT)
		fd[STDOUT_FILENO] = open(redirect->content,
				O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (redirect->type == RED_IN)
		fd[STDIN_FILENO] = open(redirect->content, O_RDONLY);
	else if (redirect->type == D_RED_IN)
		fd[STDIN_FILENO] = open_heredoc(redirect->content, vars->envp);
}

static void	duplicate_redirect_fd(t_cmd **cmd, int *fd)
{
	dup2(fd[STDIN_FILENO], STDIN_FILENO);
	if (fd[STDIN_FILENO] != STDIN_FILENO)
		(*cmd)->pipe[STDIN_FILENO] = fd[STDIN_FILENO];
	dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
	if (fd[STDOUT_FILENO] != STDOUT_FILENO && (*cmd)->next)
		(*cmd)->next->pipe[STDOUT_FILENO] = fd[STDOUT_FILENO];
}

int	duplicate_redirections(t_cmd **cmd, t_vars *vars, int is_fork)
{
	t_list	*redirect;
	int		fd[2];

	fd[STDIN_FILENO] = STDIN_FILENO;
	fd[STDOUT_FILENO] = STDOUT_FILENO;
	redirect = (*cmd)->redirect;
	while (redirect)
	{
		if (!expand_redirect(redirect, vars))
			return (0);
		open_redirect_fd(redirect, vars, fd);
		if (fd[STDIN_FILENO] == -1 || fd[STDOUT_FILENO] == -1)
		{
			if (is_fork)
				exit_perror();
			return (perror("Error"), 0);
		}
		redirect = redirect->next;
	}
	duplicate_redirect_fd(cmd, fd);
	return (1);
}
