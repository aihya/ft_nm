/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:29:07 by aihya             #+#    #+#             */
/*   Updated: 2022/04/18 18:58:37 by aihya            ###   ########.fr       */
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
            if (!strcmp(name, target))
                return (&elf->shdr[idx]);
        }
    }
    return (NULL);
}

static t_node   *concatenate(t_node *syms, t_node *secs)
{
    t_node  *node;

    if (syms == NULL)
        return (secs);
    if (secs == NULL)
        return (syms);
    node = syms;
    while (node && node->next)
        node = node->next;
    node->next = secs;
    return (syms);
}

void        elf64(void *ptr)
{
    t_elf64 *elf;
    t_node  *syms;
    t_node  *secs;
    t_node  *node;
    size_t  size;

    size = 0;
    elf = elf64_init(ptr);
    if (elf)
    {
        syms = elf64_syms(elf, &size);
        secs = elf64_secs(elf, &size);
        syms = concatenate(syms, secs);
        sort(syms);
        node = syms;
        while (node)
        {
            // ft_putendl(node->name);
            if (node->object)
                print64(elf, node);
            node = node->next;
        }
    }
}
