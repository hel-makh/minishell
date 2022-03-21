/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lstnew.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:19:55 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/21 11:10:35 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_cmd_lstnew(char **cmd, int type, int subsh_lvl, t_list *redirect)
{
	t_cmd	*element;

	element = malloc (1 * sizeof(t_cmd));
	if (element == NULL)
		return (0);
	element->cmd = cmd;
	element->type = type;
	element->subsh_lvl = subsh_lvl;
	element->redirect = redirect;
	element->next = NULL;
	return (element);
}
