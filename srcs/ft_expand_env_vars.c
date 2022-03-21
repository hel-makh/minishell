/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:41:31 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/21 22:54:13 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static void	ft_replace_var(char **envp, char **cmd, int *index)
{
	char	*var_name;
	size_t	var_len;

	var_len = ft_varname_len(&(*cmd)[*index + 1]);
	var_name = ft_substr(*cmd, *index + 1, var_len);
	if (ft_getenv(var_name, envp))
		*cmd = ft_replace_str(*cmd,
				ft_getenv(var_name, envp), *index, var_len + 1);
	else
		*cmd = ft_replace_str(*cmd, "", *index, var_len + 1);
	if (ft_getenv(var_name, envp))
		*index += ft_strlen(ft_getenv(var_name, envp)) - 1;
	var_name = ft_free(var_name);
}

static void	ft_expand_env_var(t_vars *vars, char **cmd)
{
	char	s_quote;
	int		i;

	s_quote = 0;
	i = 0;
	while ((*cmd)[i])
	{
		if (!s_quote && (*cmd)[i] == '\'')
			s_quote = (*cmd)[i];
		else if (s_quote && (*cmd)[i] == '\'')
			s_quote = 0;
		if (!s_quote && (*cmd)[i] == '$'
			&& (*cmd)[i + 1] && ft_varname_len(&(*cmd)[i + 1]))
			ft_replace_var(vars->envp, cmd, &i);
		i ++;
	}
}

int	ft_expand_env_vars(t_vars *vars)
{
	t_cmd	*cmd;
	int		i;

	cmd = vars->cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->cmd[i])
		{
			if (ft_strchr(cmd->cmd[i], '$'))
				ft_expand_env_var(vars, &cmd->cmd[i]);
			i ++;
		}
		while (cmd->redirect)
		{
			if (ft_strchr(cmd->redirect->content, '$'))
				ft_expand_env_var(vars, &cmd->redirect->content);
			cmd->redirect = cmd->redirect->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
