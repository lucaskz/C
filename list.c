#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void list_init(t_list *l){
	*l=NULL;
}

short list_empty(t_list l){
	return l==NULL;
}

t_data list_insert(t_list *l, t_data d){
	t_list_node *node = malloc(sizeof(t_list_node));
	node->data = d;
	node->next = NULL;
	if(*l==NULL)
		*l = node;
	else{
    	t_list_node *n = *l;
   	 	while (n->next) n = n->next;
   		 n->next = node;
	}
	return d;
}

void list_free(t_list *l){
	t_list_node *node = *l;
	while(node){
		t_list_node *aux = node;
		node = node->next;
		free(aux);
	}
}
