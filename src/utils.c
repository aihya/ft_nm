/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:51:53 by aihya             #+#    #+#             */
/*   Updated: 2022/04/22 14:43:40 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	alloc_node(t_node **head, t_node **curr)
{
	if (*head == NULL)
	{
		*head = (t_node *)malloc(sizeof(t_node));
		*curr = *head;
	}
	else
	{
		(*curr)->next = (t_node *)malloc(sizeof(t_node));
		*curr = (*curr)->next;
	}
}

unsigned char	switch_global(uint64_t info, char c)
{
	return (c - 32 * (info == STB_GLOBAL));
}

int	error(char *name, char *msg)
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

uint64_t	addr(t_node *node, int arch)
{
	if (arch == ELF_64)
	{
		if (node->type == ELF_SYM)
			return (((Elf64_Sym *)node->object)->st_value);
		return (((Elf64_Shdr *)node->object)->sh_addr);
	}
	else
	{
		if (node->type == ELF_SYM)
			return (((Elf32_Sym *)node->object)->st_value);
		return (((Elf32_Shdr *)node->object)->sh_addr);
	}
}