/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:29:13 by aihya             #+#    #+#             */
/*   Updated: 2022/06/17 14:56:30 by aihya            ###   ########.fr       */
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
# define ERROR -1
# define OK 1
# define STRIPPED 2

// typedef struct s_elf64
// {
// 	char		*shst;
// 	char		*strt;
// 	Elf64_Ehdr	*ehdr;
// 	Elf64_Shdr	*shdr;
// 	Elf64_Shdr	*symt;
// 	Elf64_Sym	*syms;
// }	t_elf64;

typedef struct s_elf64
{
	Elf64_Ehdr	*ehdr;
	Elf64_Shdr	*shtab;
	Elf64_Shdr	*symtsh;
	Elf64_Shdr	*strtsh;
	Elf64_Sym	*symtab;
	char		*strtab;
} t_elf64;

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
	struct s_node	*next;
}	t_node;

// hashtable
t_node		*convert_to_list(t_node **hashtable);
t_node		*find_head(t_node **hashtable);
void		add_node(t_node *node, t_node **hashtable);
t_node**	init_hashtable();

int    elf64(void *ptr);
void    elf32(void *ptr);

char    resolve_symbol_type(t_node *node, t_elf64 *elf);

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
uint64_t		addr(t_node *node, int arch);
char	switch_global(uint64_t info, char c);

#endif
