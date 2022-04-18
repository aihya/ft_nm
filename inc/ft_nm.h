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

# define SWITCH_GLOBAL(i, c) (c - 32 * (i == STB_GLOBAL))
# define TYPE_d(t) (t == SHT_INIT_ARRAY || \
					t == SHT_DYNAMIC || \
					t == SHT_FINI_ARRAY || \
					t == SHT_PROGBITS)
# define TYPE_r(t) (t == SHT_STRTAB || \
					t == SHT_PROGBITS || \
					t == SHT_DYNSYM || \
					t == SHT_NOTE || \
					t == SHT_GNU_verdef || \
					t == SHT_GNU_HASH || \
					t == SHT_GNU_versym || \
					t == SHT_GNU_verneed)
# define TYPE_b(t) (t == SHT_NOBITS)
# define TYPE_t(t) (t == SHT_PROGBITS)
# define TYPE_n(t) (t == SHT_PROGBITS)
# define FLAG_b(f) (f == SHF_ALLOC + SHF_WRITE)
# define FLAG_d(f) (f == SHF_ALLOC + SHF_WRITE)
# define FLAG_t(f) (f == SHF_ALLOC + SHF_EXECINSTR)
# define FLAG_r(f) (f & SHF_ALLOC)

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
	struct s_node	*next;
}               t_node;

// Utils
void			alloc_node(t_node **head, t_node **curr);
void			sort(t_node *nodes); 

// ELF 64
void			elf64(void *ptr);
t_elf64			*elf64_init(void *ptr);
Elf64_Shdr		*elf64_shdr(void *ptr, char *target, t_elf64 *elf);
t_node			*elf64_syms(t_elf64 *elf, size_t *size);
t_node			*elf64_secs(void *ptr, t_elf64 *elf, size_t *size);
void			print64(t_elf64 *elf, t_node *node);

// ELF 32


#endif