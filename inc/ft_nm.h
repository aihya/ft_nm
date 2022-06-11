/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:29:13 by aihya             #+#    #+#             */
/*   Updated: 2022/06/11 13:00:17 by aihya            ###   ########.fr       */
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
# include <errno.h>

# define ELF_32	EM_386
# define ELF_64	EM_X86_64
# define ELF_SYM 1
# define ELF_SEC 2
# define HT_SIZE 128

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
	char		*st;
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
	struct s_node	*prev;
}	t_node;

int				parse_args(int argc, char **argv, int *ops);
void			alloc_node(t_node **head, t_node **curr);
void			sort(t_node *nodes, int arch);
int				error(char *name, char *msg);
int				open_file(char *name, struct stat *st);
unsigned int	flag_b(uint64_t flag);
unsigned int	flag_d(uint64_t flag);
unsigned int	flag_t(uint64_t flag);
unsigned int	flag_r(uint64_t flag);
unsigned int	type_d(uint64_t type);
unsigned int	type_r(uint64_t type);
unsigned int	type_b(uint64_t type);
unsigned int	type_t(uint64_t type);
unsigned int	type_n(uint64_t type);
unsigned char	switch_global(uint64_t info, char c);
uint64_t		addr(t_node *node, int arch);

#endif
