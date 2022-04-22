/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:38:46 by aihya             #+#    #+#             */
/*   Updated: 2022/04/22 16:27:11 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	print64_addr(t_node *node)
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

static unsigned char	elf64_char(uint64_t t, uint64_t f, uint64_t i)
{
	if (type_b(t) && flag_b(f))
		return (switch_global(ELF64_ST_BIND(i), 'b'));
	else if (type_d(t) && flag_d(f))
		return (switch_global(ELF64_ST_BIND(i), 'd'));
	else if (type_t(t) && flag_t(f))
		return (switch_global(ELF64_ST_BIND(i), 't'));
	else if (type_r(t) && flag_r(f))
		return (switch_global(ELF64_ST_BIND(i), 'r'));
	else if (type_n(t))
		return ('n');
	else if (t == SHT_RELA || t == SHT_REL)
		return ('r');
	return ('?');
}

static unsigned char	elf64_sec_char(Elf64_Shdr *sec, char *name)
{
	if (ft_strncmp(name, ".debug", 6) == 0)
		return ('N');
	return (elf64_char(sec->sh_type, sec->sh_flags, sec->sh_info));
}

static unsigned char	elf64_sym_char(t_elf64 *elf, Elf64_Sym *sym)
{
	uint64_t	type;
	uint64_t	flag;

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
		return (switch_global(ELF64_ST_BIND(sym->st_info), 'c'));
	else if (sym->st_shndx == SHN_ABS)
		return (switch_global(ELF64_ST_BIND(sym->st_info), 'a'));
	type = elf->shdr[sym->st_shndx].sh_type;
	flag = elf->shdr[sym->st_shndx].sh_flags;
	return (elf64_char(type, flag, sym->st_info));
}

static void	print64_node(t_elf64 *elf, t_node *node, int ops)
{
	Elf64_Sym	*sym;

	if (node->type == ELF_SEC && (ops & OP_A))
	{
		print64_addr(node);
		ft_putchar(' ');
		ft_putchar(elf64_sec_char((Elf64_Shdr *)node->object, node->name));
		ft_putchar(' ');
		ft_putendl(node->name);
	}
	else if (node->type == ELF_SYM)
	{
		sym = (Elf64_Sym *)node->object;
		if (((ops & OP_U)
		&&	sym->st_shndx == SHN_UNDEF)
		||	((ops & OP_G)
		&&	(ELF64_ST_BIND(sym->st_info) == STB_GLOBAL 
		||	 ELF64_ST_BIND(sym->st_info) == STB_WEAK))
		||	((ops & OP_A))
		||	((ops & DFLT) && ELF64_ST_TYPE(sym->st_info) != STT_FILE))
		{
			print64_addr(node);
			ft_putchar(' ');
			ft_putchar(elf64_sym_char(elf, sym));
			ft_putchar(' ');
			ft_putendl(node->name);
		} 
	}
}

void	print64(t_elf64 *elf, t_node **hashtable, int ops)
{
	t_node	*node;

	node = NULL;
	if ((ops & OP_R) && !(ops & OP_P))
		node = reverse_list(hashtable);
	if (node == NULL)
		node = forward_list(hashtable);
	while (node)
	{
		print64_node(elf, node, ops);
		node = node->next;
	}
}