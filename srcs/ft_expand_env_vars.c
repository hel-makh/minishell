/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:41:31 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/22 21:25:55 by hel-makh         ###   ########.fr       */
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

static int	ft_expand_env_var(char **envp, char **cmd)
{
	int		index;
	size_t	var_len;
	char	*var_name;

	if (ft_has_env_var(cmd) == -1)
		return (0);
	index = ft_has_env_var(cmd);
	var_len = ft_varname_len(&(*cmd)[index + 1]);
	var_name = ft_substr(*cmd, index + 1, var_len);
	if (ft_getenv(var_name, envp))
		*cmd = ft_replace_str(*cmd,
				ft_getenv(var_name, envp), index, var_len + 1);
	else
		*cmd = ft_replace_str(*cmd, "", index, var_len + 1);
	if (ft_getenv(var_name, envp))
		index += ft_strlen(ft_getenv(var_name, envp)) - 1;
	else
		index = 0;
	var_name = ft_free(var_name);
	return (index);
}

void	ft_expand_env_vars(t_vars *vars)
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
			if (ft_strchr(cmd->cmd[i], '$'))
				i += ft_expand_env_var(vars->envp, &cmd->cmd[i]);
			i ++;
		}
		redirect = cmd->redirect;
		while (redirect)
		{
			if (ft_strchr(redirect->content, '$'))
				ft_expand_env_var(vars->envp, &redirect->content);
			redirect = redirect->next;
		}
		cmd = cmd->next;
	}
}
