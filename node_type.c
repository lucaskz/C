#include "node_type.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_data data_create(char *label,char *timer,char *text){
  int i;
  
  t_data subtitle;

  // Si devuelve feof tiene etquieta
  //strcpy(subtitle.label,lines[0]);
  //subtitle.label=malloc(sizeof(label));
  //strcpy(subtitle.label,label);
  
  subtitle.start_time=malloc(sizeof(timer));
  strcpy(subtitle.start_time,timer);

  subtitle.text=malloc(sizeof(text));
  strcpy(subtitle.text,text);

  return subtitle;
}