#include "ft_nm.h"

void        alloc_node(t_node **head, t_node **curr)
{
    if (*head == NULL)
    {
        *head = (t_node *)malloc(sizeof(t_node));
        *curr = *head;
    }
    else
    {
        (*curr)->next = (t_node *)malloc(sizeof(t_node));
        *curr = (*curr)->next;
    }
}

static int  unwanted_section(Elf64_Shdr *sec)
{
    if (sec->sh_type == SHT_NULL || sec->sh_type == SHT_SYMTAB)
        return (1);
    if (sec->sh_type == SHT_STRTAB && sec->sh_flags == 0)
        return (1);
    return (0);
}

static int  relocation(void *ptr, t_elf64 *elf, int index)
{
    Elf64_Rela  *rela;
    Elf64_Rel   *rel;

    if (elf->shdr[index].sh_type == SHT_RELA)
    {
        rela = (Elf64_Rela *)(ptr + elf->shdr[index].sh_addr);
        return (!ELF64_R_TYPE(rela->r_info));
    }
    if (elf->shdr[index].sh_type == SHT_REL)
    {
        rel = (Elf64_Rel *)(ptr + elf->shdr[index].sh_addr);
        return (!ELF64_R_TYPE(rel->r_info));
    }
    return (0);
}

t_node  *elf64_secs(void *ptr, t_elf64 *elf, size_t *size)
{
    t_node  *head;
    t_node  *curr;
    int     i;

    head = NULL;
    curr = NULL;
    i = -1;
    while (++i < elf->ehdr->e_shnum)
    {
        if (relocation(ptr, elf, i) || unwanted_section(&elf->shdr[i]))
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
