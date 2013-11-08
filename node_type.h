#ifndef _LIST_TYPE_H
#define _LIST_TYPE_H

typedef struct{
	char *start_time;
	char *end_time;
	char *label;
	char *text;

} t_data;

t_data data_create(char *,char *,char *);



#endif