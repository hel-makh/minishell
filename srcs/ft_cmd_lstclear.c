/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lstclear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:03:33 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/20 19:26:18 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		ft_lstclear(&holder->redirect);
		holder = ft_free(holder);
	}
	*lst = NULL;
}
