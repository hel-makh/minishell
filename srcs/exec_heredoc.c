/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:18:40 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/27 16:33:22 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define HEREDOC "/tmp/.minishell_hh_heredoctmp_78979346245648"

static int	ft_varname_len(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			break ;
		i ++;
	}
	return (i);
}

static void	ft_put_text_fd(char **envp, char **str, int fd)
{
	int		index;
	size_t	var_len;
	char	*var_name;

	if (!ft_strchr(*str, '$'))
		return ;
	index = 0;
	// index = ft_has_env_var(str);
	var_len = ft_varname_len(&(*str)[index + 1]);
	var_name = ft_substr(*str, index + 1, var_len);
	if (ft_getenv(var_name, envp))
		*str = ft_replace_str(*str,
				ft_getenv(var_name, envp), index, var_len + 1);
	else
		*str = ft_replace_str(*str, "", index, var_len + 1);
	var_name = ft_free(var_name);
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
	while (1)
	{
		heredoc = ft_free(heredoc);
		heredoc = readline("> ");
		if (!heredoc || ft_strcmp(heredoc, limiter) == 0)
			break ;
		heredoc = ft_stradd(heredoc, "\n");
		heredoc_text = ft_stradd(heredoc_text, heredoc);
	}
	ft_put_text_fd(envp, &heredoc_text, fd);
	heredoc = ft_free(heredoc);
	heredoc_text = ft_free(heredoc_text);
	fd = open(HEREDOC, O_RDONLY);
	if (fd == -1 || unlink(HEREDOC) == -1)
		return (-1);
	return (fd);
}
