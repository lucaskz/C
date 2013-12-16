#ifndef _T_LIST_ITERATOR_H
#define _T_LIST_ITERATOR_H
#include "list.h"
#include "list_iterator_type_linked_nodes.h"

/* Incluimos la definicion del tipo desacopladamente */





typedef struct {
  t_list list;
  t_list_index current;
} t_iterator;

/* Inicializa un iterador */
t_iterator    list_iterator_init(t_list);

/* Avanza un elmento en la lista */
void          list_iterator_next(t_iterator *);

/* Retorna el elemento actual en la lista */
t_data        list_iterator_data(t_iterator);

/* Indica si termino el recorrido */
short         list_iterator_end(t_iterator);

#endif
