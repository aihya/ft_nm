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

static void	ft_nm(void *ptr, char *name)
{
	Elf64_Ehdr	*header;

	header = (Elf64_Ehdr *)ptr;
	if (header->e_ident[EI_MAG0] != ELFMAG0
	||	header->e_ident[EI_MAG1] != ELFMAG1
	||	header->e_ident[EI_MAG2] != ELFMAG2
	||	header->e_ident[EI_MAG3] != ELFMAG3)
	{
		error(name, "file format not recognized");
		return ;
	}
	if (header->e_type != ET_REL && header->e_type != ET_DYN)
	{
		error(NULL, "supports only object files and shared objects");
		return ;
	}
	if (header->e_ident[EI_CLASS] == ELFCLASS32)
	{
		ft_putendl("Wee1");
		elf32(ptr, name);
	}
	if (header->e_ident[EI_CLASS] == ELFCLASS64)
	{
		ft_putendl("Wee2");
		elf64(ptr, name);
	}
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
    if (S_ISDIR(st->st_mode))
        return (error(name, "Is a directory"));
	if (S_ISLNK(st->st_mode))
		return (error(name, "Is a symbolic link"));
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
	ft_nm(ptr, name);
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
	// t_node **hashtable;
	// t_node *list;

	// (void)argc;
	// (void)argv;

	// hashtable = init_hashtable();

	// t_node n1;
	// t_node n2;
	// t_node n3;
	// t_node n4;

	// n1.name = "aab";
	// n2.name = "aws";
	// n3.name = "aaa";
	// n4.name = "aaa";

	// n1.object = 0x2;
	// n2.object = 0x6;
	// n3.object = 0x1;
	// n4.object = 0x9;

	// n1.next = NULL;
	// n2.next = NULL;
	// n3.next = NULL;
	// n4.next = NULL;

	// add_node(&n1, hashtable);
	// add_node(&n2, hashtable);
	// add_node(&n3, hashtable);
	// add_node(&n4, hashtable);

	// int	i = 0;
	// t_node *curr;
	// while (i < HT_SIZE)
	// {
	// 	printf("%d:\n", i);
	// 	curr = hashtable[i];
	// 	while (curr)
	// 	{
	// 		printf("%s\n", curr->name);
	// 		curr = curr->next;
	// 	}
	// 	i++;
	// }

	// list = convert_to_list(hashtable);
	// while (list)
	// {
	// 	printf("%s %d\n", list->name, (int)(list->object));
	// 	list = list->next;
	// }
}
