/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64_syms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:19:21 by aihya             #+#    #+#             */
/*   Updated: 2022/04/22 16:19:56 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

// t_node  *elf64_syms(t_elf64 *elf, size_t *size)
// {
//     t_node      *head;
//     t_node      *curr;
//     t_node      *prev;
//     uint64_t    i;

//     head = NULL;
//     curr = NULL;
//     prev = NULL;
//     i = 0;
//     while (++i < elf->symt->sh_size / sizeof(Elf64_Sym))
//     {
//         if (ELF64_ST_TYPE(elf->syms[i].st_info) != STT_SECTION)
//         {
//             alloc_node(&head, &curr);
//             curr->object = &elf->syms[i];
//             curr->name = elf->strt + elf->syms[i].st_name;
//             curr->type = ELF_SYM;
//             curr->next = NULL;
//             curr->prev = prev;
//             prev = curr;
//             (*size)++;
//         }
//     }
//     return (head);
// }

// New version with hashtable

void    elf64_syms(t_elf64 *elf, t_node **hashtable, int ops)
{
    t_node      *node;
    uint64_t    i;

    i = 0;
    while (++i < elf->symt->sh_size / sizeof(Elf64_Sym))
    {
        if (ELF64_ST_TYPE(elf->syms[i].st_info) != STT_SECTION)
        {
            node = (t_node *)malloc(sizeof(t_node));
            node->object = &elf->syms[i];
            node->name = elf->strt + elf->syms[i].st_name;
            node->type = ELF_SYM;
            ht_add_node(hashtable, node, ELF_64, ops);
        }
    }
}