#include "stack.h"
#include <stdio.h>

void stack_init(t_stack *s){
    *s=NULL;
}

int stack_top(t_stack s){
    return s->data;
}

void stack_push(t_stack *s, s_data d){
    t_stack_node *node = malloc(sizeof(t_stack_node));
    node->data = d;
    node->next = stack_empty(*s) ? NULL : *s; 
    *s = node;
    
}

s_data stack_pop(t_stack *s){
    t_stack *top=*s;
    s_data aux;
    stack_set_data(&aux,top->data);
    *s=top->next;
    free(top);
    return aux;  
}

int stack_empty(t_stack s){
    return s==NULL;
}

