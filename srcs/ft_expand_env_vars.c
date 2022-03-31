/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:41:31 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/31 11:59:14 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_varname_len(char *var_name)
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

static int	ft_has_env_var(char *str)
{
	char	s_quote;
	int		i;

	s_quote = 0;
	i = 0;
	while (str[i])
	{
		if (!s_quote && (str[i] == '"' || str[i] == '\''))
			s_quote = str[i];
		else if (s_quote && str[i] == s_quote)
			s_quote = 0;
		if (s_quote != '\''
			&& str[i] == '$'
			&& str[i + 1]
			&& (ft_varname_len(&str[i + 1]) || str[i + 1] == '?'))
			return (i);
		i ++;
	}
	return (-1);
}

void	ft_expand_env_vars(char **envp, char **str)
{
	size_t	index;
	size_t	var_len;
	char	*var_name;
	char	*var_value;

	index = 0;
	while ((*str)[index] && ft_has_env_var(&(*str)[index]) != -1)
	{
		index += ft_has_env_var(&(*str)[index]);
		var_len = ft_varname_len(&(*str)[index + 1]);
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
}
