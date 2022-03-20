/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isatty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:03:03 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/28 15:11:55 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
    int fd = 1;

    // fd = open("tests/stat.c", O_RDONLY);
    // if (fd == -1)
    //     return (1);
    if (isatty(fd))
        printf("%d is a tty\n", fd);
    else
        printf("%d is not a tty\n", fd);
    printf("the name of the tty: %s\n", ttyname(fd));
    printf("ttyslot: %d\n", ttyslot());
    return (0);
}
