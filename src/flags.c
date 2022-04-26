/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:55:40 by aihya             #+#    #+#             */
/*   Updated: 2022/04/26 11:40:16 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

unsigned int	flag_b(uint64_t flag)
{
	return (flag == (SHF_ALLOC | SHF_WRITE));
}

unsigned int	flag_d(uint64_t flag)
{
	return ((flag & (SHF_ALLOC | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE));
}

unsigned int	flag_r(uint64_t flag)
{
	return ((flag & (SHF_ALLOC | SHF_EXECINSTR | SHF_WRITE)) == SHF_ALLOC);
}

unsigned int	flag_t(uint64_t flag)
{
	return (flag == (SHF_ALLOC | SHF_EXECINSTR));
}