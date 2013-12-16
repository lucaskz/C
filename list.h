#ifndef _T_LIST_H
#define _T_LIST_H
#include "list_type.h"
#include "linked_list_type.h"


void list_init(t_list *);

short list_empty (t_list );

t_data list_insert(t_list *, t_data );

void list_free(t_list *);

#endif
