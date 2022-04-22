/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:43:44 by aihya             #+#    #+#             */
/*   Updated: 2022/04/22 14:43:45 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	swap(t_node *node1, t_node *node2)
{
	void		*tmp0;
	char		*tmp1;
	uint16_t	tmp2;

	tmp0 = node1->object;
	tmp1 = node1->name;
	tmp2 = node1->type;
	node1->object = node2->object;
	node1->name = node2->name;
	node1->type = node2->type;
	node2->object = tmp0;
	node2->name = tmp1;
	node2->type = tmp2;
}

void		sort(t_node *nodes, int arch)
{
	t_node	*node1;
	t_node	*node2;

	if (!nodes || !nodes->next)
		return ;
	node1 = nodes;
	while (node1)
	{
		node2 = node1->next;
		while (node2 && ft_strcmp(node1->name, node2->name) <= 0)
		{
			if (ft_strcmp(node1->name, node2->name) == 0
				&& addr(node1, arch) > addr(node2, arch))
				break ;
			node2 = node2->next;
		}
		if (node2)
			swap(node1, node2);
		else
			node1 = node1->next;
	}
}
