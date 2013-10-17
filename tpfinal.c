
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[]){
  
  FILE *fin,*fout;

  if( argc <= 1 ){
	printf("missing argument");
	return EXIT_SUCCESS;
  }

/* primer pasada */
  int i;
  for(i=1; i < argc; i++){
    if( !(strcmp (argv[i],"-f")) && (argc > (i+1) ) ){
      fin=fopen(argv[i+1], "r");
      continue;
    }
    if( !(strcmp (argv[i],"-o")) && (argc > (i+1) ) ) {
      /*strcpy (fout, argv[i+1]);*/
      fout=fopen(argv[i+1], "w");
      continue;
    }    
  }

  for(i=1; i < argc;i++){
  	if ((argv[i][0]=='-') && (strlen(argv[i])==2) ){
  	  switch (argv[i][1]) {
  	    case 'f' : printf("se envio f");i++;break;
  	    case 'v' : printf("se envio v");break;
  	    case 'm' : printf("se envio m");break;
  	    case 'o' : printf("se envio o");i++;break;
  	    case 's' : printf("se envio s");break;
  	    case 'b' : printf("se envio b");break;
  	    case 'd' : printf("se envio d");break;
  	    case 'M' : printf("se envio M");break;
  	    default : printf("caso invalido");break;
  	  }
  	}
  }
  
}