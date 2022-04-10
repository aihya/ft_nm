#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <elf.h>
#include <sys/types.h>
#include <string.h>

#define __ELF_32	EM_386
#define __ELF_64	EM_X86_64

typedef struct	s_elf64_tab
{
	Elf64_Ehdr	*ehdr;
	Elf64_Ehdr	*shdr;
	Elf64_Shdr	*symt;
	Elf64_Shdr	*strt;
	Elf64_Shdr	*shst;
}				t_elf64_tab;

int		pr_error(char *msg) // Contains printf
{
	printf("%s\n", msg);
	return (EXIT_FAILURE);
}

int		ft_nm(void *ptr, struct stat *st)
{
	Elf64_Ehdr	*header;

	header = (Elf64_Ehdr *)ptr;
	if (header->e_type != ET_EXEC && header->e_type != ET_DYN)
		return (ET_NONE);
	if (header->e_machine != EM_386 && header->e_machine != EM_X86_64)
		return (ET_NONE);
	return (header->e_type);
}

Elf64_Shdr	*get_shdr(void *ptr, char *name)
{
	int			idx;
	Elf64_Ehdr	*ehdr;
	Elf64_Shdr	*shdr;
	Elf64_Shdr	*shstrtab;

	if (ptr && name)
	{
		idx = -1;
		ehdr = (Elf64_Ehdr *)ptr;
		shdr = (Elf64_Shdr *)(ptr + ehdr->e_shoff);
		shstrtab = &shdr[ehdr->e_shstrndx];
		while (++idx < ehdr->e_shnum)
		{
			if (!strcmp(ptr + shstrtab->sh_offset + shdr[idx].sh_name, name))
				return (&shdr[idx]);
		}
	}
	return (NULL);
}

t_elf64_tab	*init_elf64_tab(void *ptr)
{
	t_elf64_tab	*tab;

	if (ptr)
	{
		tab = (t_elf64_tab *)malloc(sizeof(t_elf64_tab));
		if (elf64_tab)
		{
			tab->ehdr = (Elf64_Ehdr *)(ptr);
			tab->shdr = (Elf64_Shdr *)(ptr + ehdr->e_shoff);
			tab->symt = get_shdr(ptr, ".symtab");
			tab->strt = get_shdr(ptr, ".strtab");
			tab->shst = ehdr[shdr->sh_offset];
		}
	}
	return (elf64_tab);
}

void	elf64(void *ptr)
{
	t_elf64_tab	*tab;
	char		**syms;
	int			nsyms;
	int			index;

	tab = init_elf64_tab(ptr);
	if (tab && (tab->ehdr->e_machine == ELF_64 || tab->ehdr->e_machine == ELF_32))
	{
		nsyms = tab->symt->sh_size / sizeof(Elf64_Sym);
		syms = malloc(sizeof(char *) * nsyms);
		index = 0;
		while (++index < nsyms)
		{
			// TODO: append symbols names to 'char **syms'.
		}
	}
}

void	elf32()
{
	
}


int main(int argc, char **argv)
{
	struct stat	st;
	int			fd;
	int			ret;
	void		*ptr;

	if (argc != 2)
		return pr_error("ft_nm need a file name.\n");

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return pr_error("open failed.\n");

	ret = fstat(fd, &st);
	if (ret < 0)
		return pr_error("fstat failed.\n");

	ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
		return pr_error("mmap failed.\n");

	ft_nm(ptr, &st);
	elf64(ptr);

	if (munmap(ptr, st.st_size) < 0)
		return pr_error("munmap failed.\n");

	return (EXIT_SUCCESS);
}
