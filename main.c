#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "node_type.h"

int create_file(FILE *fout,t_list *list){
    t_list_node *aux = *list;
    while(aux){
        fwrite(&aux->data,sizeof(t_data),1,fout);
        aux=aux->next;
    }
    fclose(fout);
    return 1;
}
int es_starter(char *texto,int init, int close){
    int aux=init;
    aux++;
    while((texto[aux]==' ')&&(aux<close)){
        aux++;
    }
    if( aux<close && texto[aux]!='/' ){
        if ( aux+1 <= close ){
            return 1;
        }
    }
            
    return 0;
}

int same_tag(char *texto,int init,int close,int init_2,int close_2){

    while( (texto[init]==' ') && init < close ){
        init++;
    }
    while ( (texto[init_2]==' ') && init_2<close_2 ){
        init_2++;
    }
    if(texto[init_2]!= '/' || init==close || init_2 == close_2) return 0; // no es cierre de tag. 
    
    if( init_2 < close_2 )  // si es menor directamente retorno q no es tag  ;deberia estar en /
        init_2++;
    else
        return 0;  
    
    while( texto[init] == texto[init_2] && ( init < close || init_2 < close_2 ) ){
        
        init++;
        init_2++;
    }
    if (  texto[init] != texto[init_2] &&  init < close   )   // son distintos y no llegue al final del < ... > 
        return 0;
    
    return 1;
}

int delete_tags(char *texto, int inicio ,int  fin ){
    //int num=inicio;
    int init=-1;
    int close=-1;
    int encontre=0;
    while (( (inicio<fin) || (texto[inicio]!='\0')) && (! encontre ) ) { // por si falla strlen.
        if((texto[inicio]=='<') && (init==-1)){
            init=inicio;
        }        
        if((texto[inicio]=='>')&&(close==-1)){
            close=inicio;
        }
        if(init!=-1 && close!=-1){
            if(es_starter(texto,init,close))
                 encontre=1;
            else{
                init=-1;
                close=-1;
            }
        }
        inicio++;
    }
    int encontre2=0;
    int init_2=-1;
    int close_2=-1;
    while (( (inicio<fin) || (texto[inicio]!='\0')) && ( ! encontre2 ) ) { // por si falla strlen.
        if((texto[inicio]=='<') && (init_2==-1)){
            init_2=inicio;
        }        
        if((texto[inicio]=='>')&&(close_2==-1)){
            close_2=inicio;
        }
        if(init_2!=-1 && close_2!=-1){
            if ( same_tag(texto,init+1,close,init_2+1,close_2)){
                delete_tags(texto,close+1,fin);
                encontre2=1;
            }
            else{
                  init_2=-1;
                  close_2=1;
            }        
        }
        inicio++;
    }    
    return 0;
}


int  verify(t_list *list){
    t_list_node *aux = *list;
    while(aux){
        delete_tags(aux->data.text , 0 , strlen(aux->data.text)); // 0 : inicio del string ; strlen hasta donde
    };
    return 1;
}

int read_file(FILE *fin,t_list *list){
  
  char *buffer=NULL, *texto = NULL;
  ssize_t leidos=0;
  t_data subtitle;
  size_t alocados = 10;
  int tiempo_leido,indice=1;
  int size_texto=0;
  

 
  list_init(list);        
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
    
    
    while(leidos >= 0){
      leidos = getline(&buffer,&alocados,fin);
      if(*buffer == '\n' || *buffer == '\r' || leidos==-1){  // inserto en la lista,es un elemento
        set_indice(indice,&subtitle);
        set_texto(texto,&subtitle,size_texto);
        list_insert(list,copy_data(subtitle));  // insertando..
        break;
      }
      if(size_texto == 0){
        texto = malloc((leidos + 1)* sizeof(char));
        strcpy(texto,buffer);
        size_texto = leidos;
      }
      else{
        size_texto=size_texto+leidos; 
        texto = realloc(texto,(size_texto+1)* sizeof(char));
        strcat(texto,buffer);
        
      }
    }
    free(buffer);
    buffer=NULL;
    free(texto);
    texto=NULL;   
    indice++;
    size_texto=0;
     
  }
  // subtitle_free(&subtitle);
  
  

return 1;
}

int main (int argc, char* argv[]){
  
  FILE *fin,*fout;
  t_list subtitle_input;

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
  	    case 'f' : i++;read_file(fin,&subtitle_input); break;
  	    case 'v' : verify(&subtitle_input);break;
  	    case 'm' : printf("se envio m");break;
  	    case 'o' : i++;create_file(fout,&subtitle_input);break;
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
