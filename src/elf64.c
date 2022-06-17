/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:46:42 by aihya             #+#    #+#             */
/*   Updated: 2022/06/17 16:03:38 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void    print_addr(t_node *node)
{
    if (((Elf64_Sym *)node->object)->st_value)
        ft_putnbr_base(((Elf64_Sym *)node->object)->st_value, 16, 16);
    else
        ft_putstr("                ");
}

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


int init_elf64(void *ptr, t_elf64 *elf)
{
    elf->ehdr = (Elf64_Ehdr *)ptr;
    elf->shtab = (Elf64_Shdr *)(ptr + elf->ehdr->e_shoff);
    elf->symtsh = get_shdr(ptr, ".symtab", elf);
    if (elf->symtsh == NULL)
        return (STRIPPED);
    elf->strtsh = get_shdr(ptr, ".strtab", elf);
    elf->symtab = (Elf64_Sym *)(ptr + elf->symtsh->sh_offset);
    elf->strtab = (char *)(ptr + elf->strtsh->sh_offset);
    return (OK);
}


void    read_symbols(void *ptr, t_node **hashtable, t_elf64 *elf)
{
    int i;
    t_node  *node;

    i = 0;
    while (i < elf->symtsh->sh_size / sizeof(Elf64_Sym))
    {
        node = malloc(sizeof(t_node));
        node->object = &(elf->symtab[i]);
        node->name = elf->strtab + elf->symtab[i].st_name;
        add_node(node, hashtable);
        i++;
    }
}


int    elf64(void *ptr)
{
    t_node  **hashtable;
    t_node  *symbols;
    t_node  *curr;
    t_elf64 elf;

    hashtable = init_hashtable();
    if (init_elf64(ptr, &elf) == STRIPPED)
        return (STRIPPED);
    read_symbols(ptr, hashtable, &elf);
    symbols = convert_to_list(hashtable);
    curr = symbols;
    while (curr)
    {
        if ((ELF64_ST_TYPE(((Elf64_Sym *)curr->object)->st_info) != STT_FILE
        &&  ELF64_ST_TYPE(((Elf64_Sym *)curr->object)->st_info) != STT_SECTION))
        {
            print_addr(curr);
            ft_putchar(' ');
            ft_putchar(resolve_symbol_type(curr, &elf));
            ft_putchar(' ');
            ft_putendl(curr->name);
        }
        curr = curr->next;
    }
}