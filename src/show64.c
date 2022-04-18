#include "ft_nm.h"

static void print64_addr(t_node *node)
{
    if (node->type == ELF_SEC)
    {
        if (((Elf64_Shdr *)node->object)->sh_type == SHN_UNDEF)
            ft_putstr("                ");
        else
            ft_putnbr_base(((Elf64_Shdr *)node->object)->sh_addr, 16, 16);
    }
    else
    {
        if (((Elf64_Sym *)node->object)->st_shndx == SHN_UNDEF)
            ft_putstr("                ");
        else
            ft_putnbr_base(((Elf64_Sym *)node->object)->st_value, 16, 16);
    }
}

static unsigned char    elf64_char(uint64_t t, uint64_t f, uint64_t i)
{
    if ((TYPE_b(t)) && FLAG_b(f))
        return (SWITCH_GLOBAL(ELF64_ST_BIND(i), 'b'));
    if ((TYPE_d(t)) && FLAG_d(f))
        return (SWITCH_GLOBAL(ELF64_ST_BIND(i), 'd'));
    if ((TYPE_t(t)) && FLAG_t(f))
        return (SWITCH_GLOBAL(ELF64_ST_BIND(i), 't'));
    if ((TYPE_r(t)) && FLAG_r(f))
        return (SWITCH_GLOBAL(ELF64_ST_BIND(i), 'r'));
    if ((TYPE_n(t)))
        return ('n');
    if (t == SHT_RELA || t == SHT_REL)
        return ('r');
    return (' ');
}

static unsigned char    elf64_sec_char(Elf64_Shdr *sec)
{
    return (elf64_char(sec->sh_type, sec->sh_flags, sec->sh_info));
}

static unsigned char    elf64_sym_char(t_elf64 *elf, Elf64_Sym *sym)
{
    uint64_t    type;
    uint64_t    flag;

    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    {
        if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
        {
            if (sym->st_shndx == SHN_UNDEF)
                return ('v');
            return ('V');
        }
        if (sym->st_shndx == SHN_UNDEF)
            return ('w');
        return ('W');
    }
    if (sym->st_shndx == SHN_UNDEF)
        return ('U');
    else if (sym->st_shndx == SHN_COMMON)
        return (SWITCH_GLOBAL(ELF64_ST_BIND(sym->st_info), 'c'));
    else if (sym->st_shndx == SHN_ABS)
        return (SWITCH_GLOBAL(ELF64_ST_BIND(sym->st_info), 'a'));

    type = elf->shdr[sym->st_shndx].sh_type;
    flag = elf->shdr[sym->st_shndx].sh_flags;
    return (elf64_char(type, flag, sym->st_info));
}

void        print64(t_elf64 *elf, t_node *node)
{
    print64_addr(node);
    ft_putchar(' ');
    if (node->type == ELF_SEC)
        ft_putchar(elf64_sec_char((Elf64_Shdr *)node->object));
    else
        ft_putchar(elf64_sym_char(elf, (Elf64_Sym *)node->object));
    ft_putchar(' ');
    ft_putendl(node->name);
}