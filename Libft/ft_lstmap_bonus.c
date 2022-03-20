/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 22:58:42 by hel-makh          #+#    #+#             */
/*   Updated: 2021/11/07 23:03:23 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*buffer;

	if (!f)
		return (lst);
	newlst = NULL;
	while (lst)
	{
		buffer = ft_lstnew(f(lst->content));
		if (buffer == NULL)
		{
			ft_lstclear(&newlst, del);
			return (0);
		}
		ft_lstadd_back(&newlst, buffer);
		lst = lst->next;
	}
	return (newlst);
}
