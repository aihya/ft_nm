/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:55:13 by aihya             #+#    #+#             */
/*   Updated: 2022/04/18 16:55:25 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

unsigned int	type_d(uint64_t type)
{
	return (t == SHT_INIT_ARRAY
		|| t == SHT_DYNAMIC
		|| t == SHT_FINI_ARRAY
		|| t == SHT_PROGBITS);
}

unsigned int	type_r(uint64_t type)
{
	return (t == SHT_STRTAB
		|| t == SHT_PROGBITS
		|| t == SHT_DYNSYM
		|| t == SHT_NOTE
		|| t == SHT_GNU_verdef
		|| t == SHT_GNU_HASH
		|| t == SHT_GNU_versym
		|| t == SHT_GNU_verneed);
}

unsigned int	type_b(uint64_t type)
{
	return (t == SHT_NOBITS);
}

unsigned int	type_t(uint64_t type)
{
	return (t == SHT_PROGBITS);
}

unsigned int	type_n(uint64_t type)
{
	return (t == SHT_PROGBITS);
}