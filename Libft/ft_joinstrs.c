/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinstrs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:23:19 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/27 19:29:40 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_joinstrs(char **array, char c)
{
	char	*str;
	size_t	i;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	i = 0;
	while (array[i])
	{
		str = ft_stradd(str, array[i]);
		if (!str)
			return (ft_free(str), NULL);
		str = ft_stradd(str, &c);
		if (!str)
			return (ft_free(str), NULL);
		i ++;
	}
	return (str);
}
