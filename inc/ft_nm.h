/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:29:13 by aihya             #+#    #+#             */
/*   Updated: 2022/04/18 18:57:49 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <elf.h>
# include <sys/types.h>
# include <string.h>
# include "libft.h"

# define ELF_32	EM_386
# define ELF_64	EM_X86_64
# define ELF_SYM 1
# define ELF_SEC 2
# define ERR_NO_SYMS 0
# define ERR_FILE_NOT_FOUND 1

typedef struct s_elf64
{
	char		*shst;
	char		*strt;
	Elf64_Ehdr	*ehdr;
	Elf64_Shdr	*shdr;
	Elf64_Shdr	*symt;
	Elf64_Sym	*syms;
}	t_elf64;

typedef struct s_elf32
{
	char		*shst;
	char		*strt;
	Elf32_Ehdr	*ehdr;
	Elf32_Shdr	*shdr;
	Elf32_Shdr	*symt;
	Elf32_Sym	*syms;
}	t_elf32;

typedef struct s_node
{
	void			*object;
	char			*name;
	uint64_t		type;
	struct s_node	*next;
}	t_node;

void			alloc_node(t_node **head, t_node **curr);
void			sort(t_node *nodes);
unsigned char	switch_global(uint64_t info, char c);
unsigned int	flag_b(uint64_t flag);
unsigned int	flag_d(uint64_t flag);
unsigned int	flag_t(uint64_t flag);
unsigned int	flag_r(uint64_t flag);
unsigned int	type_d(uint64_t type);
unsigned int	type_r(uint64_t type);
unsigned int	type_b(uint64_t type);
unsigned int	type_t(uint64_t type);
unsigned int	type_n(uint64_t type);

void			elf64(void *ptr);
t_elf64			*elf64_init(void *ptr);
Elf64_Shdr		*elf64_shdr(void *ptr, char *target, t_elf64 *elf);
t_node			*elf64_syms(t_elf64 *elf, size_t *size);
t_node			*elf64_secs(t_elf64 *elf, size_t *size);
void			print64(t_elf64 *elf, t_node *node);

void			elf32(void *ptr);
t_elf32			*elf32_init(void *ptr);
Elf32_Shdr		*elf32_shdr(void *ptr, char *target, t_elf32 *elf);
t_node			*elf32_syms(t_elf32 *elf, size_t *size);
t_node			*elf32_secs(t_elf32 *elf, size_t *size);
void			print32(t_elf32 *elf, t_node *node);

#endif
