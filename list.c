#include <list.h>
#include <stdlib.h>

void list_init(t_list *l){
	*list=NULL;
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
		t_list_node *aux = *l;
		while(aux->next)
			aux = aux->next;
		aux->next = node;
	}
	return d;
}

t_data list_delete(t_list *l, t_data d){
	if(list_find(*l,d)){
		t_list_node *prev = NULL, *node = *l;
		while(node->next){
			prev = node;
			node = node->next;
		}
		if (!prev)
			*l = node->next;
		else{
			prev->next = node->next;
		}
		free(node);
	}
	return e;
}

void list_free(t_list *l){
	t_list_node *node = *l;
	while(node){
		t_list_node *aux = node;
		node = node->next;
		free(aux);
	}
}
