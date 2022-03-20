/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:08:36 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/20 15:59:48 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize(t_list *lst)
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
