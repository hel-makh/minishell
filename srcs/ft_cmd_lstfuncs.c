/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lstfuncs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:51:40 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/30 16:52:30 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cmd_lstsize(t_cmd *lst)
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

t_cmd	*ft_cmd_lstnew(char **cmd, int type, int *subsh_lvl, t_list *redirect)
{
	t_cmd	*element;

	element = malloc (1 * sizeof(t_cmd));
	if (element == NULL)
		return (0);
	element->cmd = cmd;
	element->type = type;
	element->subsh_lvl = subsh_lvl;
	element->redirect = redirect;
	element->next = NULL;
	return (element);
}

t_cmd	*ft_cmd_lstlast(t_cmd *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	ft_cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	if (lst && *lst)
		ft_cmd_lstlast(*lst)->next = new;
	else
		*lst = new;
}

void	ft_cmd_lstclear(t_cmd **lst)
{
	t_cmd	*holder;

	if (!lst)
		return ;
	while (*lst)
	{
		holder = *lst;
		*lst = (*lst)->next;
		holder->cmd = ft_free_2d(holder->cmd);
		holder->subsh_lvl = ft_free(holder->subsh_lvl);
		ft_lstclear(&holder->redirect);
		holder = ft_free(holder);
	}
	*lst = NULL;
}
