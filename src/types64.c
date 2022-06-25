/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:19:13 by aihya             #+#    #+#             */
/*   Updated: 2022/06/25 14:59:35 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf64.h"

static char switch_global(uint64_t info, char c)
{
    if (ELF64_ST_BIND(info) & STB_GLOBAL)
        return (c - 32);
    return (c);
}


static Elf64_Shdr   *resolve_section(t_node *node, t_elf64 *elf)
{
    return (&elf->shtab[((Elf64_Sym *)node->object)->st_shndx]);
}


char        *section_name64(t_node *node, t_elf64 *elf)
{
    Elf64_Shdr  *sec;

    sec = resolve_section(node, elf);
    return ((char *)(elf->ptr + elf->shstrtab->sh_offset + sec->sh_name));
}


static int  type_d(t_node *node, t_elf64 *elf)
{
    char    *name;

    name = section_name64(node, elf);
    if (!ft_strncmp(".data", name, 5)
    ||  !ft_strcmp(".tdata", name)
    ||  !ft_strcmp(".dynamic", name)
    ||  ft_ends_with(name, "array")
    ||  ft_begins_with(name, ".got")
    ||  ft_begins_with(name, ".plt"))
        return (1);
    return (0);
}


static int  type_b(t_node *node, t_elf64 *elf)
{
    char    *name;

    name = section_name64(node, elf);
    if (!ft_strcmp(".bss", name)
    ||  !ft_strcmp(".tbss", name))
        return (1);
    return (0);
}


static int  type_t(t_node *node, t_elf64 *elf)
{
    char    *name;

    name = section_name64(node, elf);
    if (!ft_strcmp(".text", name)
    ||  !ft_strcmp(".fini", name)
    ||  !ft_strcmp(".init", name))
        return (1);
    return (0);
}


static int  type_r(t_node *node, t_elf64 *elf)
{
    char    *name;

    name = section_name64(node, elf);
    if (!ft_strncmp(".eh", name, 3)
    ||  ft_begins_with(name, ".ro"))
        return (1);
    return (0);
}


static int  type_N(t_node *node, t_elf64 *elf)
{
    char    *name;

    name = section_name64(node, elf);
    if (ft_begins_with(name, ".note"))
        return (1);
    return (0);
}


char    resolve_symbol_type64(t_node *node, t_elf64 *elf)
{
    Elf64_Sym   *sym;
    Elf64_Shdr  *sec;
    
    sym = (Elf64_Sym *)node->object;
    sec = resolve_section(node, elf);

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
    if (type_d(node, elf))
        return (switch_global(sym->st_info, 'd'));
    if (type_b(node, elf))
        return (switch_global(sym->st_info, 'b'));
    if (type_t(node, elf))
        return (switch_global(sym->st_info, 't'));
    if (type_r(node, elf))
        return (switch_global(sym->st_info, 'r'));
    if (type_N(node, elf))
        return ('N');
    return (' ');
}