#ifndef STACK_H
#define	STACK_H

#ifndef STACK_TYPE_H
#include "stack_type.h"
#endif


void stack_init(t_stack *);

int stack_top(t_stack);

int stack_empty(t_stack);

void stack_push(t_stack *, s_data);

s_data stack_pop(t_stack *);

#endif