#include "ft_nm.h"

int     error(char *name, char *msg)
{
    ft_putstr("ft_nm: ");
    if (name)
    {
        ft_putstr(name);
        ft_putstr(": ");
    }
    if (msg)
        ft_putstr(msg);
    ft_putchar('\n');
    return (ERROR);
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

int open_file(char *name, struct stat *st)
{
    int fd;

    fd = open(name, O_RDONLY);
    if (fd == ERROR && errno == EACCES)
        return (error(name, "Permission denied"));
    else if (fd == -1)
        return (error(name, "No such file or directory"));
    if (fstat(fd, st) < 0)
        return (error(name, "Permission denied"));
    else if (S_ISDIR(st->st_mode))
        return (error(name, "Is a directory"));
    return (fd);
}

int	ft_nm_file(char *name)
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
	ft_nm(ptr);
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

int	ft_nm_files(int argc, char **argv)
{
	int	i;
	int	ret;

	ret = EXIT_SUCCESS;
	i = 0;
	while (++i < argc)
	{
		if (ft_nm_file(argv[i]) == ERROR)
			ret |= EXIT_FAILURE;
	}
	return (ret);
}

int main(int argc, char **argv)
{
	if (argc - 1 == 0)
		return (ft_nm_file("./a.out"));
	return (ft_nm_files(argc, argv));
}
