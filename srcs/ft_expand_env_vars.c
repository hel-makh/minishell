/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:41:31 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/26 21:13:09 by hel-makh         ###   ########.fr       */
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

static int	ft_has_env_var(char **cmd)
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
			return (i);
		i ++;
	}
	return (-1);
}

static void	ft_expand_env_var(char **envp, char **cmd)
{
	int		index;
	size_t	var_len;
	char	*var_name;

	if (ft_has_env_var(cmd) == -1)
		return ;
	index = ft_has_env_var(cmd);
	var_len = ft_varname_len(&(*cmd)[index + 1]);
	var_name = ft_substr(*cmd, index + 1, var_len);
	if (ft_getenv(var_name, envp))
		*cmd = ft_replace_str(*cmd,
				ft_getenv(var_name, envp), index, var_len + 1);
	else
		*cmd = ft_replace_str(*cmd, "", index, var_len + 1);
	var_name = ft_free(var_name);
}

void	ft_expand_env_vars(t_cmd **cmd, t_vars *vars)
{
	t_cmd	*t_cmd;
	t_list	*redirect;
	int		i;

	t_cmd = *cmd;
	i = 0;
	while (t_cmd->cmd[i])
	{
		ft_expand_env_var(vars->envp, &t_cmd->cmd[i]);
		i ++;
	}
	redirect = t_cmd->redirect;
	while (redirect)
	{
		ft_expand_env_var(vars->envp, &redirect->content);
		redirect = redirect->next;
	}
	t_cmd = t_cmd->next;
}
