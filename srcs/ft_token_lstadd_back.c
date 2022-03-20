/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_lstadd_back.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:31:45 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/19 17:09:45 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*lstlast;

	lstlast = ft_token_lstlast(*lst);
	if (lst && *lst)
	{
		lstlast->next = new;
		new->previous = lstlast;
	}
	else
	{
		*lst = new;
		(*lst)->previous = NULL;
	}
}
