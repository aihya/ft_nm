/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:19:13 by aihya             #+#    #+#             */
/*   Updated: 2022/06/29 17:33:43 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf64.h"

static char switch_global(uint64_t info, char c)
{
    if (ELF64_ST_BIND(info) & STB_GLOBAL)
        return (c - 32);
    return (c);
}


Elf64_Shdr   *resolve_section64(t_node *node, t_elf64 *elf)
{
    if (((Elf64_Sym *)node->object)->st_shndx == SHN_ABS)
        return (NULL);
    return (&elf->shtab[((Elf64_Sym *)node->object)->st_shndx]);
}


char        *section_name64(t_node *node, t_elf64 *elf)
{
    Elf64_Shdr  *sec;

    sec = resolve_section64(node, elf);
    if (sec == NULL)
        return "\0";
    return ((char *)(elf->ptr + elf->shstrtab->sh_offset + sec->sh_name));
}


char    resolve_symbol_type64(t_node *node, t_elf64 *elf)
{
    Elf64_Sym   *sym;
    Elf64_Shdr  *sec;
    
    sym = (Elf64_Sym *)node->object;
    sec = resolve_section64(node, elf);
    if (sec == NULL)
        return (switch_global(sym->st_info, 'a'));
    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    {
        if (sec->sh_type == SHN_UNDEF)
            return (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT ? 'v' : 'w');
        return (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT ? 'V' : 'W');
    }
    if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
        return ('u');
    if (sec->sh_type == SHN_UNDEF)
        return ('U');
    if (ELF64_ST_TYPE(sym->st_info) == STT_COMMON)
        return (switch_global(sym->st_info, 'c'));
    // if (sec->sh_type == SDATA_SECTION_ASM_OP)
    //     return (switch_global(sym->st_info, 's'));
    if (sec->sh_type == SHT_NOBITS)
        return (switch_global(sym->st_info, 'b'));
    if (sec->sh_flags & SHF_EXECINSTR)
        return (switch_global(sym->st_info, 't'));
    if (sec->sh_flags & SHF_WRITE)
        return (switch_global(sym->st_info, 'd'));
    if (sec->sh_type == SHT_PROGBITS && (sec->sh_flags & SHF_ALLOC))
        return (switch_global(sym->st_info, 'r'));
    if (sec->sh_type == SHT_PROGBITS)
        return (switch_global(sym->st_info, 'n'));
    if (sec->sh_type == SHT_NOTE)
        return ('N');
    return (' ');
}