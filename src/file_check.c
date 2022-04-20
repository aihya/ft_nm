/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:31:23 by aihya             #+#    #+#             */
/*   Updated: 2022/04/20 22:06:49 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int open_file(char *name, struct stat *st)
{
    int fd;

    fd = open(name, O_RDONLY);
    if (fd == -1 && errno == EACCES)
        return (error(name, "Permission denied"));
    else if (fd == -1)
        return (error(name, "No such file or directory"));
    if (fstat(fd, st) < 0)
        return (error(name, "Permission denied"));
    else if (S_ISDIR(st->st_mode))
        return (error(name, "Is a directory"));
    return (fd);
}