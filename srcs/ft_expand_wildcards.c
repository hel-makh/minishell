/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_wildcards.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:06:35 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/27 16:06:41 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_get_files(char **envp, char *cmd, int *index)
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
			if (!index || !*index)
				break ;
		}
	}
	closedir(folder);
	return (files);
}

static int	ft_has_wildcard(char *str)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		if (!quote && str[i] == '*')
			return (1);
		i ++;
	}
	return (0);
}

int	ft_expand_wildcards(
	t_vars *vars, t_cmd **cmd, t_list **redirect, int *index
	)
{
	char	**files;
	char	*cmd_p;

	if (index)
		cmd_p = (*cmd)->cmd[*index];
	else
		cmd_p = (*redirect)->content;
	if (!ft_has_wildcard(cmd_p))
		return (0);
	files = ft_get_files(vars->envp, cmd_p, index);
	if (!files || !*files)
		return (0);
	if (index)
		(*cmd)->cmd = ft_replace_arr((*cmd)->cmd, files, *index, 1);
	else
		(*redirect)->content = ft_replace_str((*redirect)->content,
				files[0], 0, ft_strlen((*redirect)->content));
	if (index)
		*index += ft_arrlen(files) - 1;
	files = ft_free_2d(files);
	return (1);
}
