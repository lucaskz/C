
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "node_type.h"

int read_file(FILE *fin){
  
  t_list list;
  int flines=0,line_counter=0;
  char *label,*timer,*text;

  while(!feof(fin)){
    if((fgets(line,sizeof(line),fin))==NULL){       // Si se encuentra error de lectura o feof 
      if(feof(fin)) break;                          // Termina el loop si encuentra el fin
      printf("error de lectura");
    }
    if(fline>2){
      if (line_counter==0){
        if(has_label(line)){                        // Primera linea es label .. 
          *label=malloc(sizeof(line));
          strcpy(*label,line);
        }
        else{
          *timer=malloc(sizeof(line));               // Guardo timer (no tiene label)
          strcpy(*timer,line);
          line_counter++;                           // para considerar el proximo elemento como un texto
        }
      }
      if(line_counter==1){                          //Guardo timer ( tiene label )
        *timer=malloc(sizeof(line));
        strcpy(*timer,line);              
      }
      if(line_counter=>2){
        if(line_counter==2){
          *text=malloc(sizeof(line));
          strcpy(*text,line);          
        }
        else{
          //concateno strings...
        }
      }
      line_counter++;
    }
    flines++;
  }





/*                                        ----------- Vieja funcion 
  char line[100];
  int fline_number=0,line_counter=0;
  char block[100][100];
  int temp=0;
  t_list list,aux;
  
  list_init(&list);

  while(!feof(fin)){
    if((fgets(line,sizeof(line),fin))==NULL){       // Si se encuentra error de lectura o feof 
      if(feof(fin)) break;                          // Termina el loop si encuentra el fin
      printf("error de lectura");
    } 
    if(fline_number>=2){
      strcpy(block[line_counter],line);                    // Armo mi arreglo temporal
      if (line[strspn(line, " \t\v\r\n")] == '\0'){
        list_insert(&list, data_create(block,line_counter));  // Creo un nodo y lo inserto.
        line_counter=0;
      }
      else{
        line_counter++;
      }
    }
    fline_number++;
  }  
  aux=list;
  while(aux){
    printf(" Start : %s  text : %s ",aux->data.start_time,aux->data.text);
    aux=aux->next;
  }

  while (fgets(line, sizeof(line), fin) != NULL)
  {
    printf ("\n %s",line);
  }
  if(!feof(fin)) printf("error de lectura del archivo");

*/
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

