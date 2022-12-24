/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf32.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:37:54 by aihya             #+#    #+#             */
/*   Updated: 2022/06/29 16:09:36 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF32_H
# define ELF32_H

# include "ft_nm.h"
# include <elf.h>

typedef struct s_elf32
{
	void		*ptr;
	Elf32_Ehdr	*ehdr;
	Elf32_Shdr	*shtab;
	Elf32_Shdr	*shstrtab;
	Elf32_Shdr	*symtsh;
	Elf32_Shdr	*strtsh;
	Elf32_Sym	*symtab;
	char		*strtab;
} t_elf32;

Elf32_Shdr	*resolve_section32(t_node *node, t_elf32 *elf);
char		resolve_symbol_type32(t_node *node, t_elf32 *elf);
char		*section_name32(t_node *node, t_elf32 *elf);

#endif