#include "ft_nm.h"

static int	pr_error(char *msg) // Contains printf
{
	ft_putendl(msg);
	return (ERROR);
}

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
	struct stat	st;
	int			fd;
	int			ret;
	void		*ptr;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return pr_error("ft_nm: open failed.\n");
	ret = fstat(fd, &st);
	if (ret < 0)
		return pr_error("ft_nm: fstat failed.\n");
	ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
		return pr_error("ft_nm: mmap failed.\n");
	ft_nm(ptr, ops);
	if (munmap(ptr, st.st_size) < 0)
		return pr_error("ft_nm: munmap failed.\n");
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
		if (argv[i][0] != '-')
			continue ;
		if (ft_nm_file(argv[i], ops) == ERROR)
			ret |= EXIT_FAILURE;
	}
	return (ret);
}

int main(int argc, char **argv)
{
	int	ops;

	ops = parse_args(argc, argv);
	if (ops == ERROR)
		return (EXIT_FAILURE);
	if (nm_args(argc, argv, ops) == 0)
		return (ft_nm_file("./a.out", ops));
	return (ft_nm_files(argc, argv, ops));
}
