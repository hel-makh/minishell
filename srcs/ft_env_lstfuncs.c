/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lstfuncs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 23:04:16 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/24 23:12:03 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env_lstsize(t_env *lst)
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

t_env	*ft_env_lstnew(char **envp)
{
	t_env	*element;

	element = malloc (1 * sizeof(t_env));
	if (element == NULL)
		return (0);
	element->envp = envp;
	element->next = NULL;
	return (element);
}

t_env	*ft_env_lstlast(t_env *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	ft_env_lstadd_back(t_env **lst, t_env *new)
{
	if (lst && *lst)
		ft_env_lstlast(*lst)->next = new;
	else
		*lst = new;
}

void	ft_env_lstclear(t_env **lst)
{
	t_env	*holder;

	if (!lst)
		return ;
	while (*lst)
	{
		holder = *lst;
		*lst = (*lst)->next;
		holder->envp = ft_free_2d(holder->envp);
		holder = ft_free(holder);
	}
	*lst = NULL;
}
