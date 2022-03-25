/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:18:40 by ybensell          #+#    #+#             */
/*   Updated: 2022/03/24 15:31:45 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	size;

	size = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[size + i] = src[i];
		i++;
	}
	dest[size + i] = '\0';
	return (dest);
}

char	*ft_strjoin_heredoc(char *s1, char *s2)
{
	char	*p;
	int		size1;
	int		size2;

	if (!s2)
		return (NULL);
	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char) * 1);
		*(s1 + 0) = '\0';
	}
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	p = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	ft_strcpy(p, s1);
	ft_strcat(p, s2);
	free(s1);
	return (p);
}

static void	write_tmp_file(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->str[i])
	{
		write(exec->fd_tmp, &exec->str[i], 1);
		i++;
	}
	if (close(exec->fd_tmp) == -1)
		exit_perror();
	exec->fd_in = open("/tmp/minishell_heredoctmp_78979346245648", O_RDONLY);
	if (exec->fd_in == -1)
		exit_perror();
	if (unlink("/tmp/minishell_heredoctmp_78979346245648") == -1)
		exit_perror();
	free(exec->str);
}

void	heredoc_exec(t_exec *exec, char *end)
{
	//g_var.heredoc = 1;
	exec->str = NULL;
	exec->fd_tmp = open("/tmp/minishell_heredoctmp_78979346245648", O_WRONLY
			| O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (exec->fd_tmp == -1)
	{
		if (unlink("/tmp/minishell_heredoctmp_78979346245648") == -1)
			exit_perror();
		exec->fd_tmp = open("/tmp/minishell_heredoctmp_78979346245648",
				O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
		if (exec->fd_tmp == -1)
			exit_perror();
	}
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		exec->line = readline("> ");
		if (!exec->line || ft_strcmp(exec->line, end) == 0)
			break ;
		exec->line = ft_strjoin_heredoc(exec->line, "\n");
		exec->str = ft_strjoin_heredoc(exec->str, exec->line);
	}
	write_tmp_file(exec);
}
