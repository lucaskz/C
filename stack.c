#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void stack_init(t_stack *s){
    *s=NULL;
}

s_data stack_top(t_stack s){
    return s->data;
}

void stack_push(t_stack *s, s_data d){
    t_stack_node *node = malloc(sizeof(t_stack_node));
    node->data = d;
    node->next = stack_empty(*s) ? NULL : *s; 
    *s = node;
    
}

s_data stack_pop(t_stack *s){
    t_stack_node *top=*s;
    s_data aux;
    stack_set_data(&aux,top->data);
    *s=top->next;
    free(top);
    return aux;  
}

int stack_empty(t_stack s){
    return s==NULL;
}

void stack_free(t_stack *s){
	t_stack_node *data = *s;
	while(data){
		t_stack_node *aux = data;
		data = data->next;
		free(aux);
	}
}