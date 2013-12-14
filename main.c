#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "list_iterator.h"


int create_file_srt(FILE *fout,t_list *list){
    t_iterator it;
    for (it=list_iterator_init(*list); !list_iterator_end(it); list_iterator_next(&it))
    {     
        fprintf(fout,"%d\n%.2d:%.2d:%.2d,%.3d --> %.2d:%.2d:%.2d,%.3d\n%s\n",list_iterator_data(it).indice,
                                                            list_iterator_data(it).start.hora,list_iterator_data(it).start.min,
                                                            list_iterator_data(it).start.seg,list_iterator_data(it).start.mil,
                                                            list_iterator_data(it).end.hora,list_iterator_data(it).end.min,list_iterator_data(it).end.seg,
                                                            list_iterator_data(it).end.mil,
                                                            list_iterator_data(it).text);
    } 
    fclose(fout);
    return 1;
}


int es_close(char *texto,int init, int close){
    init++;
    if( (init+1)<close && texto[init]=='/' ){
        return 1;
    }
            
    return 0;
}

int same_tag(char *texto,int act_init,int act_close,int aux_init,int aux_close){  
    act_init=act_init+2;
    aux_init++;
    char act=texto[act_init];
    char aux=texto[aux_init];
    while ( (act_init < act_close  && aux_init < aux_close ) && ( texto[aux_init]!=' ' && texto[act_init]!=' ' )){
        if(texto[act_init]!=texto[aux_init])  // <b> .. </i> 
            return 0;   
        act_init++;
        aux_init++;
        act=texto[act_init];
        aux=texto[aux_init];
    }
    if( texto[act_init]==' ' && aux_init<aux_close ) return 0;  //  <ba> ... </b>
    
    if( texto[aux_init]==' ' && act_init<act_close ) return 0;  // <b> .. </ba>
    
    return 1;
}

int clear_tag(char *texto, int act_init,int act_close,int aux_init,int aux_close,int *fin){
    int i,d;
    for(i=aux_init,d=aux_close+1;d<*fin;i++,d++){
        texto[i]=texto[d];
    }
    int desplazamiento=aux_close-aux_init+1;
    *fin=*fin-desplazamiento;
    act_close=act_close-desplazamiento;
    act_init=act_init-desplazamiento;
    for(i=act_init,d=act_close+1;d<*fin;i++,d++){
        texto[i]=texto[d];
    }
    desplazamiento=act_close-act_init+1;
    *fin=*fin-desplazamiento;
    texto[*fin]='\0';
    return 1;
}


int delete_tags(char *texto, int inicio ,int  fin ){
    int act_init=-1;
    int act_close=-1;
    int aux_init=-1;
    int aux_close=-1;
    int act=inicio;
    
    while  ( act<fin || texto[act]!='\0' ){
        if((texto[act]=='<') && (act_init==-1)){
            if(act+1<=fin &&texto[act+1]!=' ')act_init=act;            
        }        
        if((texto[act]=='>')&&(act_close==-1)&&(act_init!=-1)){
            act_close=act;
        }
        if(act_init!=-1 && act_close!=-1){
            if(aux_init==-1 && aux_close==-1){
                if(es_close(texto,act_init,act_close)){
                    printf("\n error en : %s",texto);
                    return 0;
                } //recibo como primer </> un cierre; esta mal ,termino ejecucion
                aux_init=act_init;
                aux_close=act_close;
                act_init=-1;
                act_close=-1;
            }
            else{
                if(es_close(texto,act_init,act_close)){
                    if(same_tag(texto,act_init,act_close,aux_init,aux_close)){
                        clear_tag(texto,act_init,act_close,aux_init,aux_close,&fin);
                        aux_init=-1;
                        aux_close=-1;
                        act_init=-1;
                        act_close=-1;
                        act=inicio-1; // por el act++..
                    }
                    else{
                        printf("\n no cumple %s",texto);
                        return 0;
                    }
                }
                else{
                    aux_init=act_init;
                    aux_close=act_close;
                    act_init=-1;
                    act_close=-1;
                }
            }
            
        }
        act++;
    }
    if ((act_init==-1 || act_close==-1 ) && ( aux_init!=-1 || aux_close!=-1)){
        printf("\n no cumple %s",texto);
            return 0;
            
    }
    printf("\n cumple %s",texto);
}

int  verify(t_list *list){
    t_iterator it;
    for (it=list_iterator_init(*list); !list_iterator_end(it); list_iterator_next(&it))
    {
      delete_tags(list_iterator_data(it).text , 0 , strlen(list_iterator_data(it).text)); // 0 : inicio del string ; strlen hasta donde
    } 
    return 1;
}

int read_file_webvtt(FILE *fin,t_list *list){
  
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
  subtitle_free(&subtitle);
  
  

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
  	    case 'f' : i++;read_file_webvtt(fin,&subtitle_input); break;
  	    case 'v' : verify(&subtitle_input);break;
  	    case 'm' : printf("se envio m");break;
  	    case 'o' : i++;create_file_srt(fout,&subtitle_input);break;
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

