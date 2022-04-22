#include "ft_nm.h"

static void	ft_nm(void *ptr, int ops)
{
	Elf64_Ehdr	*header;

	header = (Elf64_Ehdr *)ptr;
	if (header->e_type != ET_REL && header->e_type != ET_DYN)
		return ;
	if (header->e_machine != EM_386 && header->e_machine != EM_X86_64)
		return ;
	if (header->e_machine == ELF_32)
		elf32(ptr, ops);
	else if (header->e_machine == ELF_64)
		elf64(ptr, ops);
}

int	num_files(int argc, char **argv)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-')
			c++;
	}
	return (c);
}

int	ft_nm_file(char *name, int ops)
{
	int			fd;
	void		*ptr;
	struct stat	st;

	fd = open_file(name, &st);
	if (fd == ERROR)
		return (EXIT_FAILURE);
	ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
	{
		error("mmap", "Failed to map file to memory");
		return (EXIT_FAILURE);
	}
	ft_nm(ptr, ops);
	if (munmap(ptr, st.st_size) < 0)
	{
		error("munmap", "Failed to unmap file from memory");
		return (EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		error("close", "Failed to close file descriptor");
		return (EXIT_FAILURE);
	}
	return (1);
}

int	ft_nm_files(int argc, char **argv, int ops)
{
	int	i;
	int	ret;

	ret = EXIT_SUCCESS;
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
			continue ;
		if (ft_nm_file(argv[i], ops) == ERROR)
			ret |= EXIT_FAILURE;
	}
	return (ret);
}

int main(int argc, char **argv)
{
	int	ops;
	int	names;

	ops = DFLT;
	names = parse_args(argc, argv, &ops);
	if (ops == ERROR)
		return (EXIT_FAILURE);
	if (names == 0)
		return (ft_nm_file("./a.out", ops));
	return (ft_nm_files(argc, argv, ops));
}
