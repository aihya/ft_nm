/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf32_syms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:02:33 by aihya             #+#    #+#             */
/*   Updated: 2022/04/19 13:37:33 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_node  *elf32_syms(t_elf32 *elf, size_t *size)
{
    t_node      *head;
    t_node      *curr;
    t_node      *prev;
    uint32_t    i;

    head = NULL;
    curr = NULL;
    prev = NULL;
    i = 0;
    while (++i < elf->symt->sh_size / sizeof(Elf32_Sym))
    {
        if (ELF32_ST_TYPE(elf->syms[i].st_info) != STT_SECTION)
        {
            alloc_node(&head, &curr);
            curr->object = &elf->syms[i];
            curr->name = elf->strt + elf->syms[i].st_name;
            curr->type = ELF_SYM;
            curr->next = NULL;
            curr->prev = prev;
            prev = curr;
            (*size)++;
        }
    }
    return (head);
}
