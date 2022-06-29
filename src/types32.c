/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:19:13 by aihya             #+#    #+#             */
/*   Updated: 2022/06/29 16:08:38 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf32.h"

static char switch_global(uint32_t info, char c)
{
    if (ELF32_ST_BIND(info) & STB_GLOBAL)
        return (c - 32);
    return (c);
}


Elf32_Shdr   *resolve_section32(t_node *node, t_elf32 *elf)
{
    if (((Elf32_Sym *)node->object)->st_shndx == SHN_ABS)
        return (NULL);
    return (&elf->shtab[((Elf32_Sym *)node->object)->st_shndx]);
}


char        *section_name32(t_node *node, t_elf32 *elf)
{
    Elf32_Shdr  *sec;

    sec = resolve_section32(node, elf);
    if (sec == NULL)
        return "\0";
    return ((char *)(elf->ptr + elf->shstrtab->sh_offset + sec->sh_name));
}


char    resolve_symbol_type32(t_node *node, t_elf32 *elf)
{
    Elf32_Sym   *sym;
    Elf32_Shdr  *sec;
    
    sym = (Elf32_Sym *)node->object;
    sec = resolve_section32(node, elf);
    if (sec == NULL)
        return (switch_global(sym->st_info, 'a'));
    if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
    {
        if (sec->sh_type == SHN_UNDEF)
            return (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT ? 'v' : 'w');
        return (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT ? 'V' : 'W');
    }
    if (ELF32_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
        return ('u');
    if (sec->sh_type == SHN_UNDEF)
        return ('U');      
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