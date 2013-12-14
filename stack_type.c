#include "stack_type.h"
#include <stdio.h>

int stack_init_empty(s_data s){
    return s.init==-1;
}

int stack_close_empty(s_data s){
    return s.close==-1;
}

int stack_get_init(s_data s){
    return s.init;
}

int stack_get_close(s_data s){
    return s.close;
}

int stack_data_empty(s_data s){
    return (stack_init_empty(s) || stack_close_empty(s));
}

void stack_set_close(s_data *s,int n){
    *s.close=n;
}

void stack_set_init(s_data *s,int n){
    *s->init=n;
}


void stack_data_init(s_data *s){
    *s.init=-1;
    *s.close=-1;
}

void stack_set_data(s_data *s,s_data a){
    *s.close=a.close;
    *s.init=a.init;
}