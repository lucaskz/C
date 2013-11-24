#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "node_type.h"


int read_file(FILE *fin){
  
  t_list list;
  char *buffer=NULL;
  ssize_t leidos=0;
  t_data subtitle;
  size_t alocados = 10;
  int tiempo_leido,indice=1;

 
          
  subtitle_init(&subtitle);
  while(!feof(fin) && leidos >=0 ){
    tiempo_leido=0;
    while(leidos >= 0 && !tiempo_leido){
      leidos = getline(&buffer,&alocados,fin);
      int tiempo = es_tiempo(buffer);
      if ( tiempo ){
        if(tiempo==1){
          set_time_hour(buffer,&subtitle);
        }else{
          set_time(buffer,&subtitle);
        }
        tiempo_leido=1;
      }else {
        set_label(buffer,&subtitle);
      }
    }
    if(!tiempo_leido) {
      printf("error de estructura");
      return 0;
    }
    int size_texto=0,size_anterior = 0 ;
    char *texto = NULL;
    while(leidos >= 0){
      leidos = getline(&buffer,&alocados,fin);  
      if(*buffer == '\n' || *buffer == '\r'){  // inserto en la lista,es un elemento
        set_indice(indice,&subtitle);
        set_texto(texto,&subtitle,size_anterior);
        list_insert(&list,copy_data(subtitle));  // insertando..
        break;
      }
      if(size_texto == 0){
        texto = malloc((leidos + 1)* sizeof(char));
        strcpy(texto,buffer);
        size_texto = leidos;
      }
      else{
        texto = realloc(texto,(size_texto + leidos + 1)* sizeof(char));
        size_anterior=size_texto+leidos;
        strcat(texto,buffer);
      }
    }
    free(buffer);buffer=NULL;
    free(texto);texto=NULL;
   
    indice++;
     
  }
  // subtitle_free(&subtitle);


return 0;
}

int main (int argc, char* argv[]){
  
  FILE *fin,*fout;

  if( argc <= 1 ){
	printf("Faltan parametros use -help para mas ayuda");
	return 2;
  }

/* primer pasada */
  int i;
  for(i=1; i < argc; i++){
    if( !(strcmp (argv[i],"-f")) && (argc > (i+1) ) ){
    	/* comprobar luego si sse mando mas de 1 -f o -o  -------------------------------------*/
      fin=fopen(argv[i+1], "r");
      continue;
    }
    if( !(strcmp (argv[i],"-o")) && (argc > (i+1) ) ) {
      /*strcpy (fout, argv[i+1]);*/
      fout=fopen(argv[i+1], "w");
      continue;
    }    
  }
  if(!fin){
  	printf("No se pudo abrir el archivo de entrada");
  	return 4;
  }

  for(i=1; i < argc;i++){
  	if ((argv[i][0]=='-') && (strlen(argv[i])==2) ){
  	  switch (argv[i][1]) {
  	    case 'f' : i++;read_file(fin);break;
  	    case 'v' : printf("se envio v");break;
  	    case 'm' : printf("se envio m");break;
  	    case 'o' : i++;break;
  	    case 's' : printf("se envio s");break;
  	    case 'b' : printf("se envio b");break;
  	    case 'd' : printf("se envio d");break;
  	    case 'M' : printf("se envio M");break;
  	    default : printf("Parametro invalido use -help para mas ayuda");return 3;break;
  	  }
  	 } 
  	 else{
  	  	printf("Parametro invalido use -help para mas ayuda");
  	  	return 3;
  	 }	
  	
   }

   return 0;
  
}

