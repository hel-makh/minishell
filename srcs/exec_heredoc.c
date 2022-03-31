/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:18:40 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/31 17:01:19 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define HEREDOC "/tmp/.minishell_hh_heredoctmp_78979346245648"

static int	ft_varname_len_heredoc(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (i == 0 && var_name[i] == '?')
		{
			i ++;
			break ;
		}
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			break ;
		i ++;
	}
	return (i);
}

static int	ft_has_env_var_heredoc(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& str[i + 1]
			&& (ft_varname_len_heredoc(&str[i + 1]) || str[i + 1] == '?'))
			return (i);
		i ++;
	}
	return (-1);
}

static void	ft_put_text_fd(char **envp, char **str, int fd)
{
	size_t	index;
	size_t	var_len;
	char	*var_name;
	char	*var_value;

	index = 0;
	while ((*str)[index] && ft_has_env_var_heredoc(&(*str)[index]) != -1)
	{
		index += ft_has_env_var_heredoc(&(*str)[index]);
		var_len = ft_varname_len_heredoc(&(*str)[index + 1]);
		var_name = ft_substr(*str, index + 1, var_len);
		if (var_len == 1 && !ft_strcmp(var_name, "?"))
			var_value = ft_itoa(g_glob.exit_status);
		else if (ft_getenv(var_name, envp))
			var_value = ft_strdup(ft_getenv(var_name, envp));
		else
			var_value = ft_strdup("");
		var_name = ft_free(var_name);
		if (!var_value)
			return ;
		*str = ft_replace_str(*str, var_value, index, var_len + 1);
		index += ft_strlen(var_value);
		var_value = ft_free(var_value);
	}
	ft_putstr_fd(*str, fd);
}

static int	open_heredoc(t_cmd *cmd, char *delimiter, char **envp)
{
	char	*heredoc;
	char	*heredoc_text;

	if (pipe(cmd->heredoc) == -1)
		return (perror("Error"), 0);
	heredoc = NULL;
	heredoc_text = ft_strdup("");
	g_glob.heredoc = 1;
	while (g_glob.heredoc)
	{
		heredoc = ft_free(heredoc);
		ft_putstr_fd("> ", STDOUT_FILENO);
		heredoc = get_next_line(STDOUT_FILENO);
		if (!heredoc || (!ft_strncmp(heredoc, delimiter, ft_strlen(delimiter))
				&& ft_strlen(heredoc) - 1 == ft_strlen(delimiter)))
			break ;
		heredoc_text = ft_stradd(heredoc_text, heredoc);
	}
	if (g_glob.heredoc == 0)
		return (ft_free(heredoc), ft_free(heredoc_text), 0);
	ft_put_text_fd(envp, &heredoc_text, cmd->heredoc[STDOUT_FILENO]);
	close(cmd->heredoc[STDOUT_FILENO]);
	cmd->heredoc[STDOUT_FILENO] = -1;
	return (ft_free(heredoc), ft_free(heredoc_text), 1);
}

int	exec_init_heredoc(t_cmd **cmd, char **envp)
{
	t_cmd	*cmd_t;
	t_list	*redirect;

	cmd_t = *cmd;
	while (cmd_t)
	{
		redirect = cmd_t->redirect;
		while (redirect)
		{
			if (redirect->type == D_RED_IN)
			{
				if (cmd_t->heredoc[STDIN_FILENO] != -1
					&& cmd_t->heredoc[STDOUT_FILENO] != -1)
				{
					close(cmd_t->heredoc[STDIN_FILENO]);
					close(cmd_t->heredoc[STDOUT_FILENO]);
				}
				if (!open_heredoc(cmd_t, redirect->content, envp))
					return (0);
			}
			redirect = redirect->next;
		}
		cmd_t = cmd_t->next;
	}
	return (1);
}
