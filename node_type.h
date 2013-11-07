#ifndef _LIST_TYPE_H
#define _LIST_TYPE_H

typedef struct{
	char start_time[50];
	char end_time[30];
	char label[50];
	char text[50];

} t_data;

t_data data_create( char [][100] , int);



#endif