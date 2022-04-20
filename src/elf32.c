/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:00:52 by aihya             #+#    #+#             */
/*   Updated: 2022/04/19 20:15:52 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_elf32     *elf32_init(void *ptr)
{
    t_elf32 *elf;

    elf = NULL;
    if (ptr)
    {
        elf = (t_elf32 *)malloc(sizeof(t_elf32));
        if (elf)
        {
            elf->ehdr = (Elf32_Ehdr *)(ptr);
            elf->shdr = (Elf32_Shdr *)(ptr + elf->ehdr->e_shoff);
            elf->shst = ptr + elf->shdr[elf->ehdr->e_shstrndx].sh_offset;
            elf->symt = elf32_shdr(ptr, ".symtab", elf);
            if (elf->symt == NULL)
                return (ERR_NO_SYMS);
            elf->strt = ptr + elf32_shdr(ptr, ".strtab", elf)->sh_offset;
            elf->syms = ptr + elf->symt->sh_offset;
        }
    }
    return (elf);
}

Elf32_Shdr  *elf32_shdr(void *ptr, char *target, t_elf32 *elf)
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
    secs->prev = node;
    return (syms);
}

void        elf32(void *ptr, int ops)
{
    t_elf32 *elf;
    t_node  *syms;
    t_node  *secs;
    t_node  *tail;
    size_t  size;

    size = 0;
    elf = elf32_init(ptr);
    if (elf)
    {
        syms = elf32_syms(elf, &size);
        secs = elf32_secs(elf, &size);
        syms = concatenate(syms, secs);
        tail = NULL;
        if (ops & OP_R)
        {
            tail = syms;
            while (tail && tail->next)
                tail = tail->next;
        }
        print32(elf, syms, tail, ops);
    }
}
