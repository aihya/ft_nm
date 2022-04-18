/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:55:40 by aihya             #+#    #+#             */
/*   Updated: 2022/04/18 16:56:13 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

uint64_t int	flag_b(uint64_t flag)
{
	return (f == SHF_ALLOC + SHF_WRITE);
}

uint64_t int	flag_d(uint64_t flag)
{
	return (f == SHF_ALLOC + SHF_WRITE);
}

uint64_t int	flag_b(uint64_t flag)
{
	return (f == SHF_ALLOC + SHF_EXECINSTR);
}

uint64_t int	flag_b(uint64_t flag)
{
	return (f & SHF_ALLOC);
}