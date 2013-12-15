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

t_data set_texto(char * ,t_data *,int);

t_data set_label(char * ,t_data *);

t_data set_indice(int,t_data *);

int get_stime_hour(t_data);

int get_stime_min(t_data);

int get_stime_mil(t_data);

int get_stime_sec(t_data);

int get_etime_hour(t_data);

int get_etime_min(t_data);

int get_etime_mil(t_data);

int get_etime_seg(t_data);

char* get_texto(t_data);

char* get_label(t_data);

int get_indice(t_data);

int subtitle_free(t_data);

int es_tiempo(char *);

t_data copy_data(t_data);

int subtitle_init(t_data *);

#endif