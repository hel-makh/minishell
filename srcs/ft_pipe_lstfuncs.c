/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_lstfuncs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 23:04:16 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/25 21:21:14 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pipe_lstsize(t_pipe *lst)
{
	int	lstlen;

	lstlen = 0;
	while (lst)
	{
		lst = lst->next;
		lstlen ++;
	}
	return (lstlen);
}

t_pipe	*ft_pipe_lstnew(int input, int output)
{
	t_pipe	*element;

	element = malloc (1 * sizeof(t_pipe));
	if (element == NULL)
		return (0);
	element->fd[STDIN_FILENO] = input;
	element->fd[STDOUT_FILENO] = output;
	element->next = NULL;
	return (element);
}

t_pipe	*ft_pipe_lstlast(t_pipe *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	ft_pipe_lstadd_back(t_pipe **lst, t_pipe *new)
{
	if (lst && *lst)
		ft_pipe_lstlast(*lst)->next = new;
	else
		*lst = new;
}

void	ft_pipe_lstclear(t_pipe **lst)
{
	t_pipe	*holder;

	if (!lst)
		return ;
	while (*lst)
	{
		holder = *lst;
		*lst = (*lst)->next;
		holder = ft_free(holder);
	}
	*lst = NULL;
}
