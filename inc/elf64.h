/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:37:54 by aihya             #+#    #+#             */
/*   Updated: 2022/06/27 19:05:40 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF64_H
# define ELF64_H

# include "ft_nm.h"
# include <elf.h>

typedef struct s_elf64
{
	void		*ptr;
	Elf64_Ehdr	*ehdr;
	Elf64_Shdr	*shtab;
	Elf64_Shdr	*shstrtab;
	Elf64_Shdr	*symtsh;
	Elf64_Shdr	*strtsh;
	Elf64_Sym	*symtab;
	char		*strtab;
} t_elf64;

Elf64_Shdr	*resolve_section64(t_node *node, t_elf64 *elf);
char		resolve_symbol_type64(t_node *node, t_elf64 *elf);
char		*section_name64(t_node *node, t_elf64 *elf);

#endif