#include "ft_nm.h"

static void	ft_nm(void *ptr, int ops)
{
	Elf64_Ehdr	*header;

	header = (Elf64_Ehdr *)ptr;
	if (header->e_type & (ET_REL | ET_EXEC | ET_DYN) == 0)
		return ;
	if (header->e_machine & (EM_32 | EM_64) == 0)
		return ;
	if (header->e_machine == ELF_32)
		elf32(ptr, ops);
	else
		elf64(ptr, ops);
}

int open_file(char *name, struct stat *st)
{
    int fd;

    fd = open(name, O_RDONLY);
    if (fd == -1 && errno == EACCES)
        return (error(name, "Permission denied"));
    else if (fd == -1)
        return (error(name, "No such file or directory"));
    if (fstat(fd, st) < 0)
        return (error(name, "Permission denied"));
    else if (S_ISDIR(st->st_mode))
        return (error(name, "Is a directory"));
    return (fd);
}

int	file(char *name, int ops)
{
	int			fd;
	void		*ptr;
	struct stat	st;

	fd = open_file(name, &st);
	if (fd == -1)
		return (1);
	ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
	{
		error("mmap", "Failed to map file to memory");
		return (1);
	}
	ft_nm(ptr, ops);
	if (munmap(ptr, st.st_size) < 0)
	{
		error("munmap", "Failed to unmap file from memory");
		return (1);
	}
	if (close(fd) == -1)
	{
		error("close", "Failed to close file descriptor");
		return (1);
	}
	return (0);
}

int	files(int argc, char **argv)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (++i < argc)
	{
		if (ft_nm_file(argv[i]) == -1)
			ret |= EXIT_FAILURE;
	}
	return (ret);
}

int main(int argc, char **argv)
{
	if (argc - 1 == 0)
		return (file("./a.out"));
	return (files(argc, argv));
}
