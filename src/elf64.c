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

t_node      *elf64_syms(void *ptr, t_elf64 *elf, t_node *nodes, int *idx)
{
    while (++(*idx) < elf->symt->sh_size / sizeof(Elf64_Sym))
    {
        nodes[*idx].object = (void *)(&elf->syms[*idx]);
        nodes[*idx].name = elf->strt + elf->syms[*idx].st_name;
        nodes[*idx].type = ELF_SYM;
    }
}

t_node      *elf64_secs(void *ptr, t_elf64 *elf, t_node *nodes, int *idx)
{
    while (++(*idx) < elf->ehdr->e_shnum)
    {
        nodes[*idx].object = (void *)(&elf->shdr[*idx]);
        nodes[*idx].name = elf->shst + elf->shdr[*idx].sh_name;
        nodes[*idx].type = ELF_SEC;
    }
}

void        elf64(void *ptr)
{
    t_elf64 *elf;
    t_node  *nodes;
    size_t  size;
    int     idx;

    elf = elf64_init(ptr);
    if (elf)
    {

        size = (elf->symt->sh_size / sizeof(Elf64_Sym));
        nodes = (t_node *)malloc(sizeof(t_node) * size);
        if (nodes)
        {
            idx = 0;
            elf64_secs(ptr, elf, nodes, &idx);
            elf64_syms(ptr, elf, nodes, &idx);
            sort(nodes, idx);
            size = idx;
            idx = 0;
            while ((size_t)idx < size)
            {
                if (nodes[idx].object == NULL && ++idx)
                    continue ;
                if (nodes[idx].type == ELF_SEC)
                {
                    if (((Elf64_Shdr *)nodes[idx].object)->sh_addr == 0)
                        ft_putstr("                ");
                    else
                        ft_putnbr_base(((Elf64_Shdr *)nodes[idx].object)->sh_addr, 16, 16);
                    ft_putchar(' ');
                    ft_putendl(nodes[idx].name);
                }
                else if (nodes[idx].type == ELF_SYM)
                {
                    if (((Elf64_Sym *)nodes[idx].object)->st_value == 0)
                        ft_putstr("                ");
                    else
                        ft_putnbr_base(((Elf64_Sym *)nodes[idx].object)->st_value, 16, 16);
                    ft_putchar(' ');
                    ft_putendl(nodes[idx].name);
                }
                idx++;
            }
        }
    }
}

