#ifndef STACK_TYPE_H
#define	STACK_TYPE_H


typedef struct {
    int init;
    int close;
} s_data ;

typedef struct t_stack_node{
  struct t_stack_node *next;
  s_data data;
} *t_stack;

typedef struct t_stack_node t_stack_node;



int stack_init_empty(s_data );

int stack_close_empty(s_data );

int stack_get_init(s_data);

int stack_get_close(s_data);

void stack_set_close(s_data *,int );

void stack_set_init(s_data *,int);

void stack_data_init(s_data *);

int stack_data_empty(s_data);

void stack_set_data(s_data *,s_data );

#endif	/* STACK_TYPE_H */

