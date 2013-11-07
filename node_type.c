#include "node_type.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_data data_create(char lines[][100], int line_counter){
  int i;
  
  t_data subtitle;

  // Si devuelve feof tiene etquieta
  //strcpy(subtitle.label,lines[0]);
  strcpy(subtitle.start_time,lines[0]);
  printf("line counter %d \n" ,line_counter);
  for(i=1;i<=(line_counter-1);i++){
    strcpy(subtitle.text,lines[i]);
  }
  return subtitle;
}