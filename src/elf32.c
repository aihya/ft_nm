/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:00:00 by aihya             #+#    #+#             */
/*   Updated: 2022/07/03 17:07:42 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf32.h"

static void    print_addr(t_node *node, t_elf32 *elf)
{
    if (((Elf32_Sym *)node->object)->st_value)
        ft_putnbr_base(((Elf32_Sym *)node->object)->st_value, 16, 8);
    else
    {
        if (section_name32(node, elf)[0] || ((Elf32_Sym *)node->object)->st_shndx == SHN_ABS)
            ft_putnbr_base(0, 16, 8);
        else
            ft_putstr("        ");
    }
}


static Elf32_Shdr  *get_shdr(void *ptr, char *name, t_elf32 *elf)
{
    int i;
    Elf32_Shdr    *shstrtab;

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


static int init_elf32(void *ptr, t_elf32 *elf, struct stat *st)
{
    elf->ehdr = (Elf32_Ehdr *)ptr;
    elf->shtab = (Elf32_Shdr *)(ptr + elf->ehdr->e_shoff);
    if ((void *)elf->shtab > ptr + st->st_size)
        return (CORRUPTED);
    elf->symtsh = get_shdr(ptr, ".symtab", elf);
    if (elf->symtsh == NULL)
        return (STRIPPED);
    elf->strtsh = get_shdr(ptr, ".strtab", elf);
    elf->symtab = (Elf32_Sym *)(ptr + elf->symtsh->sh_offset);
    elf->strtab = (char *)(ptr + elf->strtsh->sh_offset);
    elf->ptr = ptr;
    elf->shstrtab = &elf->shtab[elf->ehdr->e_shstrndx];
    return (OK);
}


static void    read_symbols(t_node **hashtable, t_elf32 *elf)
{
    int i;
    t_node  *node;

    i = 0;
    while (i < (int)(elf->symtsh->sh_size / sizeof(Elf32_Sym)))
    {
        node = malloc(sizeof(t_node));
        node->object = &(elf->symtab[i]);
        node->name = elf->strtab + elf->symtab[i].st_name;
        add_node(node, hashtable);
        i++;
    }
}


int            elf32(void *ptr, char *name, struct stat *st)
{
    t_node  **hashtable;
    t_node  *symbols;
    t_node  *curr;
    t_elf32 elf;
    int     init_elf32_state;

    hashtable = init_hashtable();
    init_elf32_state = init_elf32(ptr, &elf, st);
    if (init_elf32_state == STRIPPED)
        return (error(name, "no symbols"));
    else if (init_elf32_state == CORRUPTED)
        return (error(name, "file too short"));

    read_symbols(hashtable, &elf);
    symbols = convert_to_list(hashtable);
    curr = symbols;
    while (curr)
    {
        if ((ELF32_ST_TYPE(((Elf32_Sym *)curr->object)->st_info) != STT_FILE
        &&  ELF32_ST_TYPE(((Elf32_Sym *)curr->object)->st_info) != STT_SECTION)
        &&  curr->name[0])
        {
            print_addr(curr, &elf);
            ft_putchar(' ');
            ft_putchar(resolve_symbol_type32(curr, &elf));
            ft_putchar(' ');
            ft_putendl(curr->name);
        }
        curr = curr->next;
    }
    free_hashtable(hashtable, symbols);
    return (0);
}