/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lstadd_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:31:45 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/20 18:11:46 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	if (lst && *lst)
		ft_cmd_lstlast(*lst)->next = new;
	else
		*lst = new;
}
