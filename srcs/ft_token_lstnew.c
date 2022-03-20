/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_lstnew.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:19:55 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/19 11:28:46 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_token_lstnew(char *data, int type)
{
	t_token	*element;

	element = malloc (1 * sizeof(t_token));
	if (element == NULL)
		return (0);
	element->data = data;
	element->type = type;
	element->next = NULL;
	element->previous = NULL;
	return (element);
}
