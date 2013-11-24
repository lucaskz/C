#ifndef _LIST_TYPE_H
#define _LIST_TYPE_H

struct time{
	int hora, min, seg, mil;
} ;

typedef struct{
	int indice;
	struct time start;
	struct time end;
	char *label;
	char *text;

} t_data;

t_data set_time(char * ,t_data *);

t_data set_time_hour(char * ,t_data *);

t_data set_texto(char * ,t_data *, int);

t_data set_label(char * ,t_data *);

t_data set_indice(int,t_data *);

int subtitle_free(t_data * );

int es_tiempo(char *);

t_data copy_data(t_data);

int subtitle_init(t_data *);

#endif