/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf32_secs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:02:56 by aihya             #+#    #+#             */
/*   Updated: 2022/04/18 18:57:27 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int  unwanted_section(Elf32_Shdr *sec)
{
    if (sec->sh_type == SHT_NULL || sec->sh_type == SHT_SYMTAB)
        return (1);
    if (sec->sh_type == SHT_STRTAB && sec->sh_flags == 0)
        return (1);
    return (0);
}

t_node  *elf32_secs(t_elf32 *elf, size_t *size)
{
    t_node  *head;
    t_node  *curr;
    int     i;

    head = NULL;
    curr = NULL;
    i = -1;
    while (++i < elf->ehdr->e_shnum)
    {
        if (unwanted_section(&elf->shdr[i]))
            continue ;
        alloc_node(&head, &curr);
        curr->object = &elf->shdr[i];
        curr->name = elf->shst + elf->shdr[i].sh_name;
        curr->type = ELF_SEC;
        curr->next = NULL;
        (*size)++;
    }
    return (head);
}