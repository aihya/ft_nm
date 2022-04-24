/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:39:25 by aihya             #+#    #+#             */
/*   Updated: 2022/04/23 20:45:22 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_node	**ht_init()
{
	t_node	**hashtable;

	hashtable = (t_node **)malloc(sizeof(t_node *) * HT_SIZE);
	ft_bzero(hashtable, sizeof(t_node *) * HT_SIZE);
	return (hashtable);
}

void	add_before(t_node **head, t_node *curr, t_node *node)
{
	node->next = curr;
	node->prev = curr->prev;
	if (curr == *head)
	{
		(*head)->prev = node;
		(*head) = node;
	}
	else
	{
		curr->prev->next = node;
		curr->prev = node;
	}
}

void	add_after(t_node *curr, t_node *node)
{
	node->prev = curr;
	node->next = curr->next;
	if (curr->next)
		curr->next->prev = node;
	curr->next = node;
}

void	ht_add_node(t_node **hashtable, t_node *node, int arch, int ops)
{
	t_node	*curr;
	t_node	**head;

	head = &hashtable[0];
	if (!(ops & OP_P))
		head = &hashtable[(int)node->name[0]];
	if (*head == NULL)
		*head = node;
	else
	{
		(void)arch;
		curr = *head;
		if (ops & OP_P)
		{
			while (curr && curr->next)
				curr = curr->next;
			curr->next = node;
			node->prev = curr;
			return ;
		}
		while (curr && ft_strcmp(node->name, curr->name) > 0 && curr->next)
			curr = curr->next;
		if (curr->next || ft_strcmp(node->name, curr->name) < 0)
			add_before(head, curr, node);
		else
			add_after(curr, node);
	}
}

void	print(t_node **hashtable)
{
	int		i;
	t_node	*node;

	i = -1;
	while (++i < HT_SIZE)
	{
		node = hashtable[i];
		if (node)
			printf("%d\n", i);
		while (node)
		{
			printf("\t%s\n", node->name);
			node = node->next;
		}
	}
}

t_node	*forward_list(t_node **hashtable)
{
	t_node	*head;
	t_node	*curr;
	t_node	*node;
	int		i;

	head = NULL;
	curr = NULL;
	i = -1;
	while (++i < HT_SIZE)
	{
		node = hashtable[i];
		while (node)
		{
			if (head == NULL)
				head = node;
			else
				curr->next = node;
			curr = node;
			node = node->next;
		}
	}
	return (head);
}

t_node	*reverse_list(t_node **hashtable)
{
	t_node	*head;
	t_node	*node;
	t_node	*prev;
	int		i;

	print(hashtable);
	head = NULL;
	prev = NULL;
	i = HT_SIZE;
	while (--i >= 0)
	{
		node = hashtable[i];
		while (node && node->next)
			node = node->next;
		if (head == NULL && node)
			head = node;
		if (prev && node)
		{
			prev->next = node;
			node->next = prev;
		}
		while (node)
		{
			prev = node->prev;
			node->prev = node->next;
			node->next = prev;
			prev = node;
			node = node->next;
		}
	}
	return (head);
}