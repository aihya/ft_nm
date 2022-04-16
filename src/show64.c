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

e_bind      get_bind(uint64_t info)
{
    if (ELF64_ST_BIND(info) == STB_GLOBAL)
        return (GLOBAL);
    else if (ELF64_ST_BIND(info) == STB_LOCAL)
        return (LOCAL);
    else if (ELF64_ST_BIND(info) == STB_WEAK)
        return (WEAK);
    else if (ELF64_ST_BIND(info) == STB_GNU_UNIQUE)
        return (UNIQUE);
    return (-1);
}

e_type      get_type(uint64_t info)
{
    if (ELF64_ST_TYPE(info) == STT_NOTYPE)
        return (NOTYPE);
    else if (ELF64_ST_TYPE(info) == STT_FILE)
        return (FILE_);
    else if (ELF64_ST_TYPE(info) == STT_OBJECT)
        return (OBJECT);
    else if (ELF64_ST_TYPE(info) == STT_FUNC)
        return (FUNC);
    else if (ELF64_ST_TYPE(info) == STT_SECTION)
        return (SECTION);
    return (-1);
}

static char get_weak_char(Elf64_Sym *sym)
{
    if (get_type(sym->st_info) == OBJECT)
    {
        if (sym->st_shndx == SHN_UNDEF)
            return ('v');
        return ('V');
    }
    if (sym->st_shndx == SHN_UNDEF)
        return ('w');
    return ('W');
}

static char get_extra_char(uint64_t type, uint64_t flags)
{
    if (type == SHT_NOBITS && flags == SHF_ALLOC | SHF_WRITE)
        return ('b');
    else if (type == SHT_PROGBITS && flags == SHF_ALLOC | SHF_EXECINSTR)
        return ('t');
    else if (type == SHT_PROGBITS)
        return ('n');
    else if (type == SHT_PROGBITS && flags == SHF_ALLOC | SHF_WRITE)
        return ('d');
    else if (type == SHT_PROGBITS && flags == SHF_ALLOC)
        return ('r');
    return ('?');
}

static char get_char(t_elf64 *elf, t_node *node)
{
    Elf64_Sym   *sym;
    uint64_t    info;
    uint64_t    type;
    uint64_t    flags;
    char        c;

    c = ' ';
    if (node->type == ELF_SYM)
    {
        sym = (Elf64_Sym *)node->object;
        if (get_bind(sym->st_info) == UNIQUE)
            return ('u');
        else if (get_bind(sym->st_info) == WEAK)
            return (get_weak_char(sym));
        else if (sym->st_shndx == SHN_UNDEF)
            return ('U');
        else if (sym->st_shndx == SHN_ABS)
            return ('a');
        else if (sym->st_shndx == SHN_COMMON)
            return ('c');
        info = elf->shdr[sym->st_shndx].sh_info;
        type = elf->shdr[sym->st_shndx].sh_type;
        flags = elf->shdr[sym->st_shndx].sh_flags;
        c = get_extra_char(type, flags);
    }
    else
    {
        info = ((Elf64_Shdr *)node->object)->sh_info;
        type = ((Elf64_Shdr *)node->object)->sh_type;
        flags = ((Elf64_Shdr *)node->object)->sh_flags;
        c = get_extra_char(type, flags);
    }
    if (get_bind(info) == GLOBAL && c != '?')
            return (c - 32);
    return (c);
}

void        elf64_show(t_elf64 *elf, t_node *node)
{
    print64_addr(node);
    ft_putchar(' ');
    ft_putchar(get_char(elf, node));
    ft_putchar(' ');
    ft_putstr(node->name);
    ft_putchar('\n');
}