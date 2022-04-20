/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:38:46 by aihya             #+#    #+#             */
/*   Updated: 2022/04/20 13:48:59 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	print32_addr(t_node *node)
{
	if (node->type == ELF_SEC)
	{
		if (((Elf32_Shdr *)node->object)->sh_type == SHN_UNDEF)
			ft_putstr("        ");
		else
			ft_putnbr_base(((Elf32_Shdr *)node->object)->sh_addr, 16, 8);
	}
	else
	{
		if (((Elf32_Sym *)node->object)->st_shndx == SHN_UNDEF)
			ft_putstr("        ");
		else
			ft_putnbr_base(((Elf32_Sym *)node->object)->st_value, 16, 8);
	}
}

static unsigned char	elf32_char(uint32_t t, uint32_t f, uint32_t i)
{
	if (type_b(t) && flag_b(f))
		return (switch_global(ELF32_ST_BIND(i), 'b'));
	if (type_d(t) && flag_d(f))
		return (switch_global(ELF32_ST_BIND(i), 'd'));
	if (type_t(t) && flag_t(f))
		return (switch_global(ELF32_ST_BIND(i), 't'));
	if (type_r(t) && flag_r(f))
		return (switch_global(ELF32_ST_BIND(i), 'r'));
	if (type_n(t))
		return ('n');
	if (t == SHT_RELA || t == SHT_REL)
		return ('r');
	return (' ');
}

static unsigned char	elf32_sec_char(Elf32_Shdr *sec)
{
	return (elf32_char(sec->sh_type, sec->sh_flags, sec->sh_info));
}

static unsigned char	elf32_sym_char(t_elf32 *elf, Elf32_Sym *sym)
{
	uint32_t	type;
	uint32_t	flag;

	if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
	{
		if (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT)
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
		return (switch_global(ELF32_ST_BIND(sym->st_info), 'c'));
	else if (sym->st_shndx == SHN_ABS)
		return (switch_global(ELF32_ST_BIND(sym->st_info), 'a'));
	type = elf->shdr[sym->st_shndx].sh_type;
	flag = elf->shdr[sym->st_shndx].sh_flags;
	return (elf32_char(type, flag, sym->st_info));
}

static void	print32_node(t_elf32 *elf, t_node *node, int ops)
{
	Elf32_Sym	*sym;

	if (node->type == ELF_SEC && (ops & OP_A))
	{
		print32_addr(node);
		ft_putchar(' ');
		ft_putchar(elf32_sec_char((Elf32_Shdr *)node->object));
		ft_putchar(' ');
		ft_putendl(node->name);
	}
	else if (node->type == ELF_SYM)
	{
		sym = (Elf32_Sym *)node->object;
		if (((ops & OP_U)
		&&	sym->st_shndx == SHN_UNDEF)
		||	((ops & OP_G)
		&&	(ELF32_ST_BIND(sym->st_info) == STB_GLOBAL 
		||	 ELF32_ST_BIND(sym->st_info) == STB_WEAK))
		||	((ops & OP_A))
		||	((ops & DFLT) && ELF32_ST_TYPE(sym->st_info) != STT_FILE))
		{
			print32_addr(node);
			ft_putchar(' ');
			ft_putchar(elf32_sym_char(elf, sym));
			ft_putchar(' ');
			ft_putendl(node->name);
		} 
	}
}

void	print32(t_elf32 *elf, t_node *head, t_node *tail, int ops)
{
	t_node	*node;
		
	if (!(ops & OP_P))
		sort(head);
	if (ops & OP_R && !(ops & OP_P))
	{
		node = tail;
		while (node)
		{
			print32_node(elf, node, ops);
			node = node->prev;
		}
	}
	else
	{
		node = head;
		while (node)
		{
			print32_node(elf, node, ops);
			node = node->next;
		}
	}
}
