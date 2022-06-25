/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:27:40 by aihya             #+#    #+#             */
/*   Updated: 2022/06/25 16:58:32 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf32.h"

void    print_addr(t_node *node, t_elf32 *elf)
{
    if (((Elf32_Sym *)node->object)->st_value)
        ft_putnbr_base(((Elf32_Sym *)node->object)->st_value, 16, 8);
    else
    {
        if (section_name32(node, elf)[0])
            ft_putnbr_base(0, 16, 8);
        else
            ft_putstr("        ");
    }
}


Elf32_Shdr  *get_shdr(void *ptr, char *name, t_elf32 *elf)
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


int init_elf32(void *ptr, t_elf32 *elf)
{
    elf->ehdr = (Elf32_Ehdr *)ptr;
    elf->shtab = (Elf32_Shdr *)(ptr + elf->ehdr->e_shoff);
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


void    read_symbols(void *ptr, t_node **hashtable, t_elf32 *elf)
{
    int i;
    t_node  *node;

    i = 0;
    while (i < elf->symtsh->sh_size / sizeof(Elf32_Sym))
    {
        node = malloc(sizeof(t_node));
        node->object = &(elf->symtab[i]);
        node->name = elf->strtab + elf->symtab[i].st_name;
        add_node(node, hashtable);
        i++;
    }
}


int    elf32(void *ptr)
{
    t_node  **hashtable;
    t_node  *symbols;
    t_node  *curr;
    t_elf32 elf;

    hashtable = init_hashtable();
    if (init_elf32(ptr, &elf) == STRIPPED)
        return (STRIPPED);
    read_symbols(ptr, hashtable, &elf);
    symbols = convert_to_list(hashtable);
    curr = symbols;
    while (curr)
    {
    ft_putendl(curr->name);
        if ((ELF32_ST_TYPE(((Elf32_Sym *)curr->object)->st_info) != STT_FILE
        &&  ELF32_ST_TYPE(((Elf32_Sym *)curr->object)->st_info) != STT_SECTION)
        &&  curr->name[0])
        {
            print_addr(curr, &elf);
            ft_putchar(' ');
            ft_putchar(resolve_symbol_type32(curr, &elf));
            ft_putchar(' ');
            // ft_putnbr_base(ELF32_ST_TYPE(((Elf32_Sym *)curr->object)->st_info), 2, 8);
            // ft_putchar(' ');
            // ft_putstr(resolve_section(curr, &elf)->sh_type == SHT_PROGBITS ? "TRUE " : "FALSE");
            // ft_putchar(' ');
            ft_putendl(curr->name);
            // ft_putstr(curr->name);
            // ft_putchar(' ');
            // ft_putchar('[');
            // ft_putstr(section_name(curr, &elf));
            // ft_putendl("]");
        }
        curr = curr->next;
    }
    // ft_putstr("STT_NOTYPE\t ");
    // ft_putnbr_base(STT_NOTYPE, 2, 8);
    // ft_putendl("");
    // ft_putstr("STT_OBJECT\t ");
    // ft_putnbr_base(STT_OBJECT, 2, 8);
    // ft_putendl("");
    // ft_putstr("STT_FUNC\t ");
    // ft_putnbr_base(STT_FUNC, 2, 8);
    // ft_putendl("");
    // ft_putstr("STT_SECTION\t ");
    // ft_putnbr_base(STT_SECTION, 2, 8);
    // ft_putendl("");
    // ft_putstr("STT_FILE\t ");
    // ft_putnbr_base(STT_FILE, 2, 8);
    // ft_putendl("");
    // ft_putstr("STT_LOPROC\t ");
    // ft_putnbr_base(STT_LOPROC, 2, 8);
    // ft_putendl("");
    // ft_putstr("STT_HIPROC\t ");
    // ft_putnbr_base(STT_HIPROC, 2, 8);
    // ft_putendl("");
    // ft_putstr("STB_LOCAL\t ");
    // ft_putnbr_base(STB_LOCAL, 2, 8);
    // ft_putendl("");
    // ft_putstr("STB_GLOBAL\t ");
    // ft_putnbr_base(STB_GLOBAL, 2, 8);
    // ft_putendl("");
    // ft_putstr("STB_WEAK\t ");
    // ft_putnbr_base(STB_WEAK, 2, 8);
    // ft_putendl("");
}