#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/mman.h>

void	elf(void *ptr, struct stat *st)
{
	struct Elf64_Ehdr	*hdr;

	hdr = (struct Elf64_Ehdr *)ptr;
	printf("Type: %d\n", hdr->e_type);
	printf("Machine: %d\n", hdr->e_machine);
	printf("Version: %d\n", hdr->e_version);
}

int		pr_error(char *msg)
{
	//TODO Contains: printf
	printf("%s\n", msg);
	return (EXIT_FAILURE);
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
		pr_error("open failed.\n");

	ret = fstat(fd, &st);
	if (ret < 0)
		pr_error("fstat failed.\n");

	ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
		pr_error("mmap failed.\n");

	elf(ptr, &st);

	if (munmap(ptr, st.st_size) < 0)
		pr_error("munmap failed.\n");

	return (EXIT_SUCCESS);
}
