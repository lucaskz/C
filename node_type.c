#include "node_type.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int subtitle_free(t_data *subtitle ){
  printf("\nlibero punteros..");
  free(subtitle->label);
  free(subtitle->text);
  return 1;
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
  printf("\n Tamanio de TAM : %d",tam);
  if(tam == 0 ){
    subtitle->text = malloc((strlen(text)+1) * sizeof(char));}
  else{
    subtitle->text = realloc(subtitle->text,(strlen(text)+1) * sizeof(char));}
  printf("\n  -- Aloca memoria para el texto ..");
  strcpy(subtitle->text,text);
  printf("\n Texto a copiar! : %s ",text);
  printf("\n Texto copiado : %s",subtitle->text);
  printf("\n -- Termina de copiar el texto...");
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