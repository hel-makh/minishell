/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:27:45 by hel-makh          #+#    #+#             */
/*   Updated: 2022/03/23 16:24:25 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_replace_arr(
	char **arr1, char **arr2, unsigned int start, unsigned int size
	)
{
	char	**arr;
	size_t	arr_len;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!arr1 || !arr2)
		return (NULL);
	arr_len = ft_arrlen(arr1) - size + ft_arrlen(arr2);
	arr = ft_calloc(arr_len + 1, sizeof(char *));
	i = 0;
	j = 0;
	k = 0;
	while (i < arr_len)
	{
		if (i == start)
			j += size;
		if (i < start)
			arr[i++] = ft_strdup(arr1[j++]);
		else if (i < start + ft_arrlen(arr2))
			arr[i++] = ft_strdup(arr2[k++]);
		else
			arr[i++] = ft_strdup(arr1[j++]);
	}
	return (ft_free_2d(arr1), arr);
}
