#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <elf.h>
#include <sys/types.h>

#define ELF_32	EM_386
#define ELF_64	EM_X86_64

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

Elf64_Shdr	*get_shdr(void *ptr, int type)
{
	int			i;
	Elf64_Ehdr	*ehdr;
	Elf64_Shdr	*shdr;

	if (ptr == NULL)
		return (NULL);
	ehdr = (Elf64_Ehdr *)ptr;
	shdr = (Elf64_Shdr *)(ptr + ehdr->e_shoff);

	i = -1;
	while (++i < ehdr->e_shnum)
	{
		if (shdr[i].sh_type == type)
			return (&shdr[i]);
	}
	return (NULL);
}

void	elf64(void *ptr)
{
	int			i;
	Elf64_Ehdr	*ehdr;
	Elf64_Shdr	*shdr;
	Elf64_Shdr	*__sh_symtab;
	Elf64_Shdr	*__sh_strtab;
	Elf64_Shdr	*toto;

	ehdr = (Elf64_Ehdr *)ptr;
	shdr = (Elf64_Shdr *)(ptr + ehdr->e_shoff);
	toto = &shdr[ehdr->e_shstrndx];

	__sh_symtab = get_shdr(ptr, SHT_SYMTAB);
	__sh_strtab = get_shdr(ptr, SHT_STRTAB);

	i = -1;
	while (++i < ehdr->e_shnum)
	{
		printf("%2d %s\n", i, ptr + .sh_offset + shdr[i].sh_name);
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
