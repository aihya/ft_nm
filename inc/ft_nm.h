#ifndef __FT_NM_H__
# define __FT_NM_H__

# define ELF_32	EM_386
# define ELF_64	EM_X86_64

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
	Elf64_Ehdr  *ehdr;  // ELF header
	Elf64_Shdr  *shdr;  // section header
	Elf64_Shdr  *shst;  // section header string table
	Elf64_Shdr  *symt;  // symbol table
	Elf64_Shdr  *strt;  // string table
}               t_elf64;

typedef struct  s_elf32
{
	Elf32_Ehdr  *ehdr;  // ELF header
	Elf32_Shdr  *shdr;  // section header
	Elf32_Shdr  *shst;  // section header string table
	Elf32_Shdr  *symt;  // symbol table
	Elf32_Shdr  *strt;  // string table
}               t_elf32;

typedef struct  s_dict
{
    uint64_t    name;
    uint64_t    type;
    uint64_t    addr;
}               t_dict;


// ELF 64
void            elf64(void *ptr);
t_elf64         *elf64_init(void *ptr);
Elf64_Shdr      *elf64_shdr(void *ptr, char *name, t_elf64 *elf);
char            **elf64_symtab_names(t_elf64 *tab);
char            **elf64_sections_names(t_elf64 *tab);

// ELF 32
void            elf32(void *ptr);
t_elf32         *elf32_init(void *ptr);
Elf32_Shdr      *elf32_shdr(void *ptr, char *name, t_elf32 *elf);
char            **elf32_symtab_names(t_elf32 *tab);
char            **elf32_sections_names(t_elf32 *tab);

#endif