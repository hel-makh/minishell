/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:03:33 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/20 15:59:27 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*holder;

	if (!lst)
		return ;
	while (*lst)
	{
		holder = *lst;
		*lst = (*lst)->next;
		holder->content = ft_free(holder->content);
		holder = ft_free(holder);
	}
	*lst = NULL;
}
