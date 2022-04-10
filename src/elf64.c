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
            elf->shst = (Elf64_Shdr *)(&elf->shdr[elf->ehdr->e_shstrndx]);
            elf->symt = elf64_shdr(ptr, ".symtab", elf);
            elf->strt = elf64_shdr(ptr, ".strtab", elf);
        }
    }
    return (elf);
}

Elf64_Shdr  *elf64_shdr(void *ptr, char *name, t_elf64 *elf)
{
    int idx;

    if (ptr && name && elf)
    {
        idx = -1;
        while (++idx < elf->ehdr->e_shnum)
        {
            if (!strcmp(ptr + elf->shdr->sh_offset + elf->shdr[idx].sh_name, name))
                return (&elf->shdr[idx]);
        }
    }
    return (NULL);
}

