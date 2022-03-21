/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:58:07 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/21 12:58:41 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	*ft_free_2d(char **ptr)
{
	int	i;

	if (!ptr)
		return (NULL);
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

void	*ft_free_3d(char ***ptr)
{
	int	i;

	if (!ptr)
		return (NULL);
	i = 0;
	while (ptr[i])
		ft_free_2d(ptr[i++]);
	return (NULL);
}
