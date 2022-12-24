/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:29:13 by aihya             #+#    #+#             */
/*   Updated: 2022/07/03 18:02:49 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <elf.h>
# include <sys/types.h>
# include <string.h>
# include "libft.h"
# include <errno.h>

# define ELF_32	ELFCLASS32
# define ELF_64	ELFCLASS64
# define HT_SIZE 128
# define ERROR -1
# define OK 1
# define STRIPPED 2
# define CORRUPTED 3

typedef struct s_node
{
	void			*object;
	char			*name;
	struct s_node	*next;
}	t_node; 

// hashtable

t_node		**init_hashtable();
t_node		*convert_to_list(t_node **hashtable);
t_node		*find_head(t_node **hashtable);
void		add_node(t_node *node, t_node **hashtable);
void    	free_hashtable(t_node **hashtable, t_node *list);


int         elf32(void *ptr, char *name, struct stat *st);
int         elf64(void *ptr, char *name, struct stat *st);


// Utility functions

int			parse_args(int argc, char **argv, int *ops);
void		alloc_node(t_node **head, t_node **curr);
int			error(char *name, char *msg);
int			open_file(char *name, struct stat *st);

#endif
