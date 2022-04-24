/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:55:13 by aihya             #+#    #+#             */
/*   Updated: 2022/04/24 18:40:06 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

unsigned int	type_d(uint64_t type)
{
	return ((type & SHT_INIT_ARRAY) == SHT_INIT_ARRAY
		|| (type & SHT_PREINIT_ARRAY) == SHT_PREINIT_ARRAY
		|| (type & SHT_DYNAMIC) == SHT_DYNAMIC
		|| (type & SHT_FINI_ARRAY) == SHT_FINI_ARRAY
		|| (type & SHT_PROGBITS) == SHT_PROGBITS);
}

unsigned int	type_r(uint64_t type)
{
	return ((type & SHT_STRTAB) == SHT_STRTAB
		|| (type & SHT_PROGBITS) == SHT_PROGBITS
		|| (type & SHT_DYNSYM) == SHT_DYNSYM
		|| (type & SHT_NOTE) == SHT_NOTE
		|| (type & SHT_HASH) == SHT_HASH
		|| (type & SHT_GNU_verdef) == SHT_GNU_verdef
		|| (type & SHT_GNU_HASH) == SHT_GNU_HASH
		|| (type & SHT_GNU_versym) == SHT_GNU_versym
		|| (type & SHT_GNU_verneed) == SHT_GNU_verneed
		|| (type & SHT_NOBITS) == SHT_NOBITS);
}

unsigned int	type_b(uint64_t type)
{
	return (type == SHT_NOBITS);
}

unsigned int	type_t(uint64_t type)
{
	return ((type & SHT_PROGBITS) == SHT_PROGBITS
		|| (type & SHT_NOBITS) == SHT_NOBITS);
}

unsigned int	type_n(uint64_t type)
{
	return ((type & SHT_PROGBITS) == SHT_PROGBITS
		|| (type & SHT_GROUP) == SHT_GROUP);
}