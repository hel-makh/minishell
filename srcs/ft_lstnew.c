/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:19:55 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/20 16:00:06 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_token_lstnew(char *content, int type)
{
	t_list	*element;

	element = malloc (1 * sizeof(t_list));
	if (element == NULL)
		return (0);
	element->content = content;
	element->type = type;
	element->next = NULL;
	return (element);
}
