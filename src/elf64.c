/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:29:07 by aihya             #+#    #+#             */
/*   Updated: 2022/04/25 17:46:05 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_elf64     *elf64_init(void *ptr)
{
    t_elf64 *elf;

    elf = NULL;
    if (ptr)
    {
        elf = (t_elf64 *)malloc(sizeof(t_elf64));
        if (elf)
        {
            elf->ehdr = (Elf64_Ehdr *)(ptr);
            elf->shdr = (Elf64_Shdr *)(ptr + elf->ehdr->e_shoff);
            elf->shst = ptr + elf->shdr[elf->ehdr->e_shstrndx].sh_offset;
            elf->symt = elf64_shdr(ptr, ".symtab", elf);
            if (elf->symt == NULL)
                return (ERR_NO_SYMS);
            elf->strt = ptr + elf64_shdr(ptr, ".strtab", elf)->sh_offset;
            elf->syms = ptr + elf->symt->sh_offset;
        }
    }
    return (elf);
}

Elf64_Shdr  *elf64_shdr(void *ptr, char *target, t_elf64 *elf)
{
    int     idx;
    char    *name;

    if (ptr && target && elf)
    {
        idx = -1;
        while (++idx < elf->ehdr->e_shnum)
        {
            name = elf->shst + elf->shdr[idx].sh_name;
            if (!ft_strcmp(name, target))
                return (&elf->shdr[idx]);
        }
    }
    return (NULL);
}

void        elf64(void *ptr, int ops)
{
    t_elf64 *elf;
    t_node  **hashtable;

    elf = elf64_init(ptr);
    hashtable = ht_init();
    if (elf)
    {
        elf64_syms(elf, hashtable, ops);
        elf64_secs(elf, hashtable, ops);
        print64(elf, hashtable, ops);
    }
}
