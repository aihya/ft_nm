/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:46:42 by aihya             #+#    #+#             */
/*   Updated: 2022/06/11 19:28:14 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

Elf64_Shdr  *get_shdr(void *ptr, char *name, t_elf64 *elf)
{
    int i;
    Elf64_Shdr    *shstrtab;

    shstrtab = &elf->shtab[elf->ehdr->e_shstrndx];
    i = 0;
    while (i < elf->ehdr->e_shnum)
    {
        if (!ft_strcmp(name, ptr + shstrtab->sh_offset + elf->shtab[i].sh_name))
            return (&elf->shtab[i]);
        i++;
    }
    return (NULL);
}

void    read_symbols(void *ptr, t_node **hashtable, t_elf64 *elf)
{
    int i;

    i = 0;
    while (i < elf->symtab->sh_size / sizeof(Elf64_Sym))
    {
        printf("%s\n", ptr + elf->strtab->sh_offset + elf->symtab[i].sh_name);
        i++;
    }
}

void    init_elf64(void *ptr, t_elf64 *elf)
{
    elf->ehdr = (Elf64_Ehdr *)ptr;
    elf->shtab = (Elf64_Shdr *)(ptr + elf->ehdr->e_shoff);
    elf->symtab = get_shdr(ptr, ".symtab", elf);
    elf->strtab = get_shdr(ptr, ".strtab", elf);
}

void    elf64(void *ptr)
{
    t_node  **hashtable;
    t_node  *symbols;
    t_node  *curr;
    t_elf64 elf;

    hashtable = init_hashtable();
    init_elf64(ptr, &elf);
    read_symbols(ptr, hashtable, &elf);
    // symbols = convert_to_list(hashtable);
    // curr = symbols;
    // while (curr)
    // {
    //     printf("%s\n", curr->name);
    //     curr = curr->next;
    // }
}