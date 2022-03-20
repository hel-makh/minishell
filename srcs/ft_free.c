/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:58:07 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/28 15:48:07 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

void	*ft_free_2d(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

void	*ft_free_3d(char ***ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		ft_free_2d(ptr[i++]);
	return (NULL);
}
