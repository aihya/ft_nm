/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:29:13 by aihya             #+#    #+#             */
/*   Updated: 2022/04/22 16:57:05 by aihya            ###   ########.fr       */
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
# define ERROR -1
# define ELF_SYM 1
# define ELF_SEC 2
# define ERR_NO_SYMS 0
# define ERR_FILE_NOT_FOUND 1
# define DFLT 1 << 0
# define OP_A 1 << 1
# define OP_G 1 << 2
# define OP_U 1 << 3
# define OP_R 1 << 4
# define OP_P 1 << 5
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

t_node	**ht_init();
void	ht_add_node(t_node **hashtable, t_node *node, int arch, int ops);
t_node	*forward_list(t_node **hashtable);
t_node	*reverse_list(t_node **hashtable);
void	print(t_node **hashtable);

void			elf64(void *ptr, int ops);
t_elf64			*elf64_init(void *ptr);
Elf64_Shdr		*elf64_shdr(void *ptr, char *target, t_elf64 *elf);
void			elf64_syms(t_elf64 *elf, t_node **hashtable, int ops);
void			elf64_secs(t_elf64 *elf, t_node **hashtable, int ops);
void			print64(t_elf64 *elf, t_node **hashtable, int ops);

void			elf32(void *ptr, int ops);
t_elf32			*elf32_init(void *ptr);
Elf32_Shdr		*elf32_shdr(void *ptr, char *target, t_elf32 *elf);
t_node			*elf32_syms(t_elf32 *elf, size_t *size);
t_node			*elf32_secs(t_elf32 *elf, size_t *size);
void			print32(t_elf32 *elf, t_node *head, t_node *tail, int ops);

#endif
