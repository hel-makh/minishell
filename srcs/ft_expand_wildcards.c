/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_wildcards.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:06:35 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/22 21:06:46 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_remove_quotes(char *s)
{
	char	*str;
	int		quotes;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	quotes = 0;
	i = -1;
	while (s[++i])
		if ((s[i] == '"' || s[i] == '\'') && ft_strchr(&s[i + 1], s[i]))
			quotes ++;
	str = ft_calloc((ft_strlen(s) - quotes) + 1, sizeof(char));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if ((s[i] != '"' && s[i] != '\'')
			|| ((s[i] == '"' || s[i] == '\'') && !ft_strchr(&s[i + 1], s[i])))
			str[j++] = s[i];
		i ++;
	}
	return (free(s), str);
}

static char	**ft_get_files(char **envp, char *cmd, int index)
{
	DIR				*folder;
	struct dirent	*entry;
	char			**files;

	files = ft_calloc(1, sizeof(char *));
	if (!files)
		return (NULL);
	folder = opendir(ft_getenv("PWD", envp));
	if (!folder)
		return (NULL);
	while (1)
	{
		entry = readdir(folder);
		if (!entry)
			break ;
		if (entry->d_name[0] != '.' && !ft_wc_strcmp(cmd, entry->d_name))
		{
			files = ft_add_str2arr(files, entry->d_name);
			if (!index || index == -1)
				break ;
		}
	}
	closedir(folder);
	return (files);
}

static int	ft_has_wildcard(t_cmd **cmd, t_list **redirect, int index)
{
	char	*cmd_p;
	char	quote;
	int		i;

	if (index != -1)
		cmd_p = (*cmd)->cmd[index];
	else
		cmd_p = (*redirect)->content;
	quote = 0;
	i = 0;
	while (cmd_p[i])
	{
		if (!quote && (cmd_p[i] == '\'' || cmd_p[i] == '"'))
			quote = cmd_p[i];
		else if (quote && cmd_p[i] == quote)
			quote = 0;
		if (!quote && cmd_p[i] == '*')
			return (1);
		i ++;
	}
	return (0);
}

static int	ft_expand_wildcard(
	t_vars *vars, t_cmd **cmd, t_list **redirect, int index
	)
{
	char	**files;
	char	*cmd_without_quotes;
	char	*cmd_p;

	if (!ft_has_wildcard(cmd, redirect, index))
		return (0);
	if (index != -1)
		cmd_p = (*cmd)->cmd[index];
	else
		cmd_p = (*redirect)->content;
	files = ft_get_files(vars->envp, cmd_p, index);
	if (!files || !*files)
	{
		cmd_without_quotes = ft_remove_quotes(ft_strdup(cmd_p));
		files = ft_add_str2arr(files, cmd_without_quotes);
		cmd_without_quotes = ft_free(cmd_without_quotes);
	}
	if (index != -1)
		(*cmd)->cmd = ft_replace_arr((*cmd)->cmd, files, index, 1);
	else
		(*redirect)->content = ft_replace_str((*redirect)->content,
				files[0], 0, ft_strlen((*redirect)->content));
	index = ft_arrlen(files) - 1;
	files = ft_free_2d(files);
	return (index);
}

void	ft_expand_wildcards(t_vars *vars)
{
	t_cmd	*cmd;
	t_list	*redirect;
	int		i;

	cmd = vars->cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->cmd[i])
		{
			if (ft_strchr(cmd->cmd[i], '*'))
				i += ft_expand_wildcard(vars, &cmd, NULL, i);
			i ++;
		}
		redirect = cmd->redirect;
		while (redirect)
		{
			if (ft_strchr(redirect->content, '*'))
				ft_expand_wildcard(vars, NULL, &redirect, -1);
			redirect = redirect->next;
		}
		cmd = cmd->next;
	}
}
