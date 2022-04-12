#include "ft_nm.h"

static void    swap(t_node *node1, t_node *node2)
{
    void        *tmp_object;
    char        *tmp_name;
    uint64_t    tmp_type;

    tmp_object = node1->object;
    tmp_name = node1->name;
    tmp_type = node1->type;
    node1->object = node2->object;
    node1->name = node2->name;
    node1->type = node2->type;
    node2->object = tmp_object;
    node2->name = tmp_name;
    node2->type = tmp_type;
}

void            sort(t_node *nodes, size_t size)
{
    int     i;
    int     j;
    void    *tmp;

    i = 0;
    while (i < size)
    {
        if (nodes[i].object == NULL && ++i)
            continue;
        j = i + 1;
        while (j < size)
        {
            if (nodes[j].object == NULL && ++j)
                continue;
            if (strcmp(nodes[i].name, nodes[j].name) > 0)
                swap(&nodes[i], &nodes[j]);
            j++;
        }
        i++;
    }
}