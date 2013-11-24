#include "node_type.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int subtitle_free(t_data *subtitle ){
    if(subtitle->text!= NULL) free(subtitle->text);   
    if(subtitle->label!=NULL) free(subtitle->label);    
  return 1;
}


int subtitle_init(t_data *subtitle){
    subtitle->label=NULL;
    subtitle->text=NULL;
    subtitle->indice=0;
    subtitle->start.hora=0;
    subtitle->start.seg=0;
    subtitle->start.min=0;
    subtitle->start.mil=0;
    subtitle->end.hora=0;
    subtitle->end.min=0;
    subtitle->end.seg=0;
    subtitle->end.mil=0;
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

t_data set_texto(char *text, t_data *subtitle,int tam){
  if(tam == 0 ){
    subtitle->text = malloc((strlen(text)+1) * sizeof(char));}
  else{
    subtitle->text = realloc(subtitle->text,(strlen(text)+1) * sizeof(char));}
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