/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:42:23 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/28 14:48:48 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
    DIR             *dir;
    struct dirent   *dirent;

    dir = opendir("includes");
    if (!dir)
        return (printf("error\n"), 1);
    dirent = readdir(dir);
    printf("%hu", dirent->d_namlen);
    closedir(dir);
    return (0);
}
