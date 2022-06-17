/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:19:13 by aihya             #+#    #+#             */
/*   Updated: 2022/06/17 16:16:40 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char       switch_global(uint64_t info, char c)
{
    if (ELF64_ST_BIND(info) & STB_GLOBAL)
        return (c - 32);
    return (c);
}

static Elf64_Shdr   *resolve_section(t_node *node, t_elf64 *elf)
{
    return (&elf->shtab[((Elf64_Sym *)node->object)->st_shndx]);
}

char    resolve_symbol_type(t_node *node, t_elf64 *elf)
{
    Elf64_Sym   *sym;
    Elf64_Shdr  *sec;
    
    sym = (Elf64_Sym *)node->object;
    sec = resolve_section(node, elf);

    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
                return (switch_global(sym->st_info, 'w'));

    else if (   sec->sh_type == SHN_UNDEF)
                return (switch_global(sym->st_info, 'u'));

    else if (   sec->sh_type == SHT_PROGBITS
    &&          sec->sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
                return (switch_global(sym->st_info, 't'));

    else if (   sec->sh_type == SHT_NOBITS
    &&          sec->sh_flags == (SHF_ALLOC | SHF_WRITE))
                return (switch_global(sym->st_info, 'b'));

    else if ((  sec->sh_type == SHT_DYNAMIC 
    ||          sec->sh_type == SHT_INIT_ARRAY
    ||          sec->sh_type == SHT_FINI_ARRAY
    ||          sec->sh_type == SHT_PREINIT_ARRAY)
    ||      (   sec->sh_type == SHT_PROGBITS
    &&          sec->sh_flags == (SHF_ALLOC | SHF_WRITE)))
                return (switch_global(sym->st_info, 'd'));

    else if (   sec->sh_type == SHT_PROGBITS)
                return (switch_global(sym->st_info, 'r'));
    return (' ');
}