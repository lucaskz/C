#ifndef _T_LIST_H
#define _T_LIST_H

#include "linked_list_type.h"


void list_init(t_list *);

short list_empty (t_list );

short list_find(t_list, t_data);

t_data list_insert(t_list *, t_data );

t_data list_del(t_list *, t_data );

void list_free(t_list *);

#endif

/*
void getTimeStart(Lista *, int);
void getTimeEnd(Lista *, int);
void getText(Lista *, int);
void getIndex(Lista *);

void setTimerStart();
void setTimeEnd();
void setText();
void setIndex()
*/