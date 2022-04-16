#include "ft_nm.h"

t_node  *elf64_syms(void *ptr, t_elf64 *elf, size_t *size)
{
    t_node  *head;
    t_node  *curr;
    int     i;

    head = NULL;
    curr = NULL;
    i = 0;
    while (++i < elf->symt->sh_size / sizeof(Elf64_Sym))
    {
        if (ELF64_ST_TYPE(elf->syms[i].st_info) != STT_SECTION)
        {
            alloc_node(&head, &curr);
            curr->object = &elf->syms[i];
            curr->name = elf->strt + elf->syms[i].st_name;
            curr->type = ELF_SYM;
            curr->next = NULL;
            (*size)++;
        }
    }
    return (head);
}
