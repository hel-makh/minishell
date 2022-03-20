/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_lstadd_back.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:31:45 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/20 15:58:27 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst && *lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}
