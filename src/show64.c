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

static unsigned char    elf64_sec_char(t_elf64 *elf, Elf64_Shdr *sec)
{
    return ('-');
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

    if (type == SHT_NOBITS && flag & SHF_ALLOC && flag & SHF_WRITE)
        return (SWITCH_GLOBAL(ELF64_ST_BIND(sym->st_info), 'b'));
    else if ((type == SHT_PROGBITS || type == SHT_DYNAMIC) && flag & SHF_ALLOC && flag & SHF_WRITE)
        return (SWITCH_GLOBAL(ELF64_ST_BIND(sym->st_info), 'd'));
    else if (type == SHT_PROGBITS && flag & SHF_ALLOC && flag & SHF_EXECINSTR)
        return (SWITCH_GLOBAL(ELF64_ST_BIND(sym->st_info), 't'));
    else if (type == SHT_PROGBITS && flag & SHF_AL  LOC)
        return (SWITCH_GLOBAL(ELF64_ST_BIND(sym->st_info), 'r'));
    return (' ');
}

void        print64(t_elf64 *elf, t_node *node)
{
    print64_addr(node);
    ft_putchar(' ');
    if (node->type == ELF_SEC)
        ft_putchar(elf64_sec_char(elf, (Elf64_Shdr *)node->object));
    else
        ft_putchar(elf64_sym_char(elf, (Elf64_Sym *)node->object));
    ft_putchar(' ');
    ft_putendl(node->name);
}