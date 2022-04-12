#include "ft_nm.h"

void        elf64_show(t_node *node)
{
    if (node->type == ELF_SEC)
    {
        if (((Elf64_Shdr *)node->object)->sh_type == SHT_NULL)
            ft_putstr("                ");
        else
            ft_putnbr_base(((Elf64_Shdr *)node->object)->sh_addr, 16, 16);
        ft_putchar(' ');
        ft_putendl(node->name);
    }
    else if (node->type == ELF_SYM)
    {
        if (((Elf64_Sym *)node->object)->st_value == 0)
            ft_putstr("                ");
        else
            ft_putnbr_base(((Elf64_Sym *)node->object)->st_value, 16, 16);
        // ft_putchar(' ');
        // ft_putchar(ELF64_ST_TYPE(((Elf64_Sym *)node->object)->st_info) + 65);
        ft_putchar(' ');
        ft_putendl(node->name);
    }
}