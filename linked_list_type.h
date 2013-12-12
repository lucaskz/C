#ifndef _LIST_TYPE_LINKED_NODES_H
#define _LIST_TYPE_LINKED_NODES_H
#include "list_type.h"


typedef struct t_list_node{
  struct t_list_node *next;
  t_data data;
} *t_list;

typedef struct t_list_node t_list_node;

#endif
