#ifndef STACK_H
#define	STACK_H
#include "stack_type.h"

void stack_init(t_stack *);

s_data stack_top(t_stack);

int stack_empty(t_stack);

void stack_push(t_stack *, s_data);

s_data stack_pop(t_stack *);

void stack_free(t_stack *);

#endif