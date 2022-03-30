/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:18:40 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/30 09:50:37 by ybensell         ###   ########.fr       */
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
		if (!var_value)
			return ;
		*str = ft_replace_str(*str, var_value, index, var_len + 1);
		index += ft_strlen(var_value);
		var_name = ft_free(var_name);
		var_value = ft_free(var_value);
	}
	ft_putstr_fd(*str, fd);
}

int	open_heredoc(char *limiter, char **envp)
{
	int		fd;
	char	*heredoc;
	char	*heredoc_text;
	
	fd = open(HEREDOC, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (fd);
	heredoc = NULL;
	heredoc_text = ft_strdup("");
	g_glob.heredoc = 1;
	while (g_glob.heredoc)
	{
		heredoc = ft_free(heredoc);
		heredoc = get_next_line(0);
		if (!heredoc || ft_strncmp(heredoc, limiter,ft_strlen(limiter)) == 0)
			break ;
		heredoc_text = ft_stradd(heredoc_text, heredoc);
	}
	if (g_glob.heredoc == 0)
			return (-2);
	ft_put_text_fd(envp, &heredoc_text, fd);
	heredoc = ft_free(heredoc);
	heredoc_text = ft_free(heredoc_text);
	fd = open(HEREDOC, O_RDONLY);
	if (fd == -1 || unlink(HEREDOC) == -1)
		return (-1);
	return (fd);
}
