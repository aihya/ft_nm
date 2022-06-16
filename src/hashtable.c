/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:30:16 by aihya             #+#    #+#             */
/*   Updated: 2022/06/16 10:11:47 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_node**    init_hashtable()
{
    t_node  **hashtable;

    hashtable = (t_node **)malloc(sizeof(t_node *) * HT_SIZE);
    ft_bzero(hashtable, sizeof(t_node *) * HT_SIZE);
    return (hashtable);
}


void    add_node(t_node *node, t_node **hashtable)
{
    t_node          *curr;
    t_node          *prev;

    curr = hashtable[(int)(node->name[0])];
    if (curr == NULL)
    {
        hashtable[(int)(node->name[0])] = node;
        return ;
    }
    else if (ft_strcmp(node->name, curr->name) < 0)
    {
        node->next = curr;
        hashtable[(int)(node->name[0])] = node;
        return ;
    }
    prev = NULL;
    while (curr)
    {
        if (ft_strcmp(node->name, curr->name) < 0)
            break;
        prev = curr;
        curr = curr->next;
    }
    node->next = prev->next;
    prev->next = node;
}


t_node  *find_head(t_node **hashtable)
{
    t_node  *head;
    int     i;

    head = NULL;
    i = 0;
    while (i < HT_SIZE && hashtable[i] == NULL)
        i++;
    if (i < HT_SIZE)
        head = hashtable[i];
    return (head);
}


t_node  *convert_to_list(t_node **hashtable)
{
    t_node  *head;
    t_node  *tail;
    t_node  *curr;
    int     i;

    tail = NULL;
    head = NULL;
    i = 0;
    while (i < HT_SIZE)
    {
        if (hashtable[i])
        {
            if (head == NULL)
                head = hashtable[i];
            if (tail)
            {
                tail->next = hashtable[i];
                tail = tail->next;
            }
            curr = hashtable[i];
            tail = curr;
            while (curr)
            {
                tail = curr;
                curr = curr->next;
            }
        }
        i++;
    }
    return (head);
}