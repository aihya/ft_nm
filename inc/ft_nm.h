#ifndef __FT_NM_H__
# define __FT_NM_H__

# define ELF_32	EM_386
# define ELF_64	EM_X86_64
# define ELF_SYM 0
# define ELF_SEC 1

# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <elf.h>
# include <sys/types.h>
# include <string.h>

typedef struct  s_elf64
{
	char		*shst;  // section header string table
	char		*strt;  // string table section header
	Elf64_Ehdr  *ehdr;  // ELF header
	Elf64_Shdr  *shdr;  // section headers
	Elf64_Shdr	*symt;  // symbol table section header
	Elf64_Sym	*syms;	// symbol table
}               t_elf64;

typedef struct  s_elf32
{
	char		*shst;  // section header string table
	char		*strt;  // string table section header
	Elf32_Ehdr  *ehdr;  // ELF header
	Elf32_Shdr  *shdr;  // section headers
	Elf32_Shdr	*symt;  // symbol table section header
	Elf32_Sym	*syms;	// symbol table
}               t_elf32;

typedef struct  s_node
{
    void			*object;
	char			*name;
	uint64_t		type;
}               t_node;

// ELF 64
void            elf64(void *ptr);
t_elf64         *elf64_init(void *ptr);
Elf64_Shdr      *elf64_shdr(void *ptr, char *target, t_elf64 *elf);
t_node			*elf64_syms(void *ptr, t_elf64 *elf, t_node *nodex, int *idx);
t_node			*elf64_secs(void *ptr, t_elf64 *elf, t_node *nodex, int *idx);

// ELF 32
void            elf32(void *ptr);
t_elf32         *elf32_init(void *ptr);
Elf32_Shdr      *elf32_shdr(void *ptr, char *target, t_elf32 *elf);
char            **elf32_syms(void *ptr, t_elf32 *elf, t_node *nodex, int *idx);
char            **elf32_secs(void *ptr, t_elf32 *elf, t_node *nodex, int *idx);

#endif