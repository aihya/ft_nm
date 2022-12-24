/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:22:55 by aihya             #+#    #+#             */
/*   Updated: 2022/07/03 16:59:35 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


static int	ft_nm(void *ptr, char *name, struct stat *st)
{
	Elf64_Ehdr	*header;

	header = (Elf64_Ehdr *)ptr;
	if (header->e_ident[EI_MAG0] != ELFMAG0
	||	header->e_ident[EI_MAG1] != ELFMAG1
	||	header->e_ident[EI_MAG2] != ELFMAG2
	||	header->e_ident[EI_MAG3] != ELFMAG3)
		return (error(name, "file format not recognized"));
	if (header->e_type != ET_REL && header->e_type != ET_DYN)
		return (error(NULL, "supports only object files and shared objects"));
	if (header->e_ident[EI_CLASS] == ELFCLASS32)
		return (elf32(ptr, name, st));
	if (header->e_ident[EI_CLASS] == ELFCLASS64)
		return (elf64(ptr, name, st));
	return (error(name, "supports only 64-bits or 32-bits elf files"));
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
    return (fd);
}


int	ft_nm_file(char *name)
{
	int			ret;
	int			fd;
	void		*ptr;
	struct stat	st;

	fd = open_file(name, &st);
	if (fd == ERROR)
		return (ERROR);

	ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
		return (error("mmap", "Failed to map file to memory"));

	ret = ft_nm(ptr, name, &st);
	if (munmap(ptr, st.st_size) < 0)
		return (error("munmap", "Failed to unmap file from memory"));

	if (close(fd) == -1)
		return (error("close", "Failed to close file descriptor"));
		
	return (ret);
}


int	ft_nm_files(int argc, char **argv)
{
	int	i;
	int	ret;

	ret = EXIT_SUCCESS;
	i = 0;
	while (++i < argc)
	{
		ft_putchar('\n');
		ft_putstr(argv[i]);
		ft_putendl(":");
		if (ft_nm_file(argv[i]) == ERROR)
			ret |= ERROR;
	}
	return (ret);
}


int main(int argc, char **argv)
{
	if (argc - 1 == 0)
		return (ft_nm_file("./a.out"));
	else if (argc - 1 == 1)
		return (ft_nm_file(argv[1]));
	return (ft_nm_files(argc, argv));
}
