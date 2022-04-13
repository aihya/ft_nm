#include "ft_nm.h"

static void print64_addr(t_node *node, int type)
{
    if (type == ELF_SEC)
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

static void print64_sec_type(t_elf64 *elf, t_node *node)
{
    Elf64_Shdr  *sec;
    char        c;

    c = ' ';
    sec = (Elf64_Shdr *)node->object;
    if (sec->sh_type == SHT_NULL)
        c = 'U';
    else if (sec->sh_type == SHN_COMMON)
        c = 'C';
    else if (sec->sh_type == SHT_NOBITS
         && sec->sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'B';
    else if (sec->sh_type == SHT_PROGBITS
         && sec->sh_flags == 0)
        c = 'N';
    else if (sec->sh_type == SHT_PROGBITS
         && sec->sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'D';
    else if (sec->sh_type == SHT_PROGBITS
         && sec->sh_flags == SHF_ALLOC)
        c = 'R';
    else if (sec->sh_type == SHT_PROGBITS
         && sec->sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        c = 'T';

    if (ELF64_ST_BIND(sec->sh_info) == STB_LOCAL && c != '?')
        c += 32;
    ft_putchar(' ');
    ft_putchar(c);
    ft_putchar(' ');
}

static void print64_sym_type(t_elf64 *elf, t_node *node)
{
    Elf64_Sym   *sym;
    char        c;

    c = ' ';
    sym = (Elf64_Sym *)node->object;

    if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK
          && ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
    {
        c = 'V';
        if (sym->st_shndx == SHN_UNDEF)
            c = 'v';
    }
    else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    {
        c = 'W';
        if (sym->st_shndx == SHN_UNDEF)
            c = 'w';
    }
    else if (sym->st_shndx == SHN_UNDEF)
        c = 'U';
    else if (sym->st_shndx == SHN_ABS)
        c = 'A';
    else if (sym->st_shndx == SHN_COMMON)
        c = 'C';
    else if (elf->shdr[sym->st_shndx].sh_type == SHT_PROGBITS
         && elf->shdr[sym->st_shndx].sh_flags == SHF_ALLOC)
        c = 'R';
    else if (elf->shdr[sym->st_shndx].sh_type == SHT_NOBITS
         && elf->shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'B';
    else if (elf->shdr[sym->st_shndx].sh_type == SHT_PROGBITS
         && elf->shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'D';
    else if (elf->shdr[sym->st_shndx].sh_type == SHT_PROGBITS
         && elf->shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        c = 'T';
   

    if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
        c += 32;

    ft_putchar(' ');
    ft_putchar(c);
    ft_putchar(' ');
}

void        elf64_show(t_elf64 *elf, t_node *node)
{
    if (node->type == ELF_SEC)
    {
        print64_addr(node, ELF_SEC);
        print64_sec_type(elf, node);
        ft_putendl(node->name);
    }
    else if (node->type == ELF_SYM)
    {
        print64_addr(node, ELF_SYM);
        print64_sym_type(elf, node);
        ft_putendl(node->name);
    }
}