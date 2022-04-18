#include "ft_nm.h"

static int	pr_error(char *msg) // Contains printf
{
	ft_putendl(msg);
	return (EXIT_FAILURE);
}

static void	ft_nm(void *ptr)
{
	Elf64_Ehdr	*header;

	header = (Elf64_Ehdr *)ptr;
	if (header->e_type != ET_REL && header->e_type != ET_DYN)
		return ;
	if (header->e_machine != EM_386 && header->e_machine != EM_X86_64)
		return ;
	if (header->e_machine == ELF_32)
		elf32(ptr);
	else if (header->e_machine == ELF_64)
		elf64(ptr);
	
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

	ft_nm(ptr);

	if (munmap(ptr, st.st_size) < 0)
		return pr_error("munmap failed.\n");

	return (EXIT_SUCCESS);
}
