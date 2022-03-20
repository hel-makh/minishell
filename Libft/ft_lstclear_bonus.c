/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 22:42:02 by hel-makh          #+#    #+#             */
/*   Updated: 2021/11/07 22:57:51 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*holder;

	if (!del || !lst)
		return ;
	while (*lst)
	{
		holder = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(holder, del);
	}
	*lst = NULL;
}
