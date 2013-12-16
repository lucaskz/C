#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef _T_LIST_H
#include "list.h"
#endif

int subtitle_free(t_data *subtitle ){
    if(subtitle->text!= NULL) free(subtitle->text);   
    if(subtitle->label!=NULL) free(subtitle->label);    
  return 1;
}

int get_stime_hour(t_data d){
    return d.start.hora;
}

int get_stime_min(t_data d){
    return d.start.min;
}

int get_stime_mil(t_data d){
    return d.start.mil;
}

int get_stime_sec(t_data d){
    return d.start.seg;
}

int get_etime_hour(t_data d){
    return d.end.hora;
}

int get_etime_min(t_data d){
    return d.end.min;
}

int get_etime_mil(t_data d){
    return d.end.mil;
}

int get_etime_sec(t_data d){
    return d.end.seg;
}

char* get_texto(t_data d){
    return d.text;
}

char* get_label(t_data d){
    return d.label;
}

int get_indice(t_data d){
    return d.indice;
}


int subtitle_init(t_data *subtitle){
    subtitle->label=NULL;
    subtitle->text=NULL;
    subtitle->indice=00;
    subtitle->start.hora=00;
    subtitle->start.seg=00;
    subtitle->start.min=00;
    subtitle->start.mil=000;
    subtitle->end.hora=00;
    subtitle->end.min=00;
    subtitle->end.seg=00;
    subtitle->end.mil=000;
    return 1;
}


t_data copy_data(t_data subtitle){

  t_data copy;
  copy.start.hora=subtitle.start.hora;
  copy.start.min=subtitle.start.min;
  copy.start.seg=subtitle.start.seg;
  copy.start.mil=subtitle.start.mil;
  copy.end.hora=subtitle.end.hora;
  copy.end.min=subtitle.end.min;
  copy.end.seg=subtitle.end.seg;
  copy.end.mil=subtitle.end.mil;
  copy.indice=subtitle.indice;
  if(subtitle.label==NULL){
      copy.label=NULL;
  }else{
      copy.label=malloc((strlen(subtitle.label)+1) * sizeof(char));
      strcpy(copy.label,subtitle.label);
  }  
  copy.text=malloc((strlen(subtitle.text)+1) * sizeof(char));
  strcpy(copy.text,subtitle.text);
  return copy;
}

t_data set_time_hour(char *buffer, t_data *subtitle){
  sscanf(buffer, "%2d:%2d:%2d.%3d --> %2d:%2d:%2d.%3d", &subtitle->start.hora, &subtitle->start.min,
         &subtitle->start.seg,&subtitle->start.mil,&subtitle->end.hora,
        &subtitle->end.min,&subtitle->end.seg,&subtitle->end.mil);
  return (*subtitle);
}

t_data set_time(char *buffer, t_data *subtitle){
  sscanf(buffer, "%2d:%2d.%3d --> %2d:%2d.%3d", &subtitle->start.min,
         &subtitle->start.seg,&subtitle->start.mil,&subtitle->end.min,&subtitle->end.seg,&subtitle->end.mil);
  return (*subtitle);
}

t_data set_label(char *label, t_data *subtitle){
  subtitle->label=malloc((strlen(label)+1) * sizeof(char));
  strcpy(subtitle->label,label);
  return (*subtitle);
}

t_data set_texto(char *text, t_data *subtitle,int size){
  subtitle->text = malloc((size + 1)* sizeof(char));
  strcpy(subtitle->text,text);
  return (*subtitle);
}

t_data set_indice(int indice, t_data *subtitle){
   
  subtitle->indice=indice;
  return (*subtitle);
}

int es_tiempo(char *buffer){
  int hora_1,min_1,seg_1,mil_1;
  int hora_2,min_2,seg_2,mil_2;
  
  if ( sscanf(buffer,"%2d:%2d:%2d.%3d --> %2d:%2d:%2d.%3d",&hora_1,&min_1,&seg_1,&mil_1,&hora_2,&min_2,&seg_2,&mil_2) == 8 ){  // tiene hora en el tiempo...
    return 1;
  }

  if (sscanf(buffer,"%2d:%2d.%3d --> %2d:%2d.%3d",&min_1,&seg_1,&mil_1,&min_2,&seg_2,&mil_2) == 6){  // tiene hora SIN el tiempo    return 2;
    return 2;  
  }

  return 0; // no es tiempo!
}  