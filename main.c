#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "list.h"
#include "list_iterator.h"
#include "stack.h"

int create_file_srt(FILE *fout, t_list *list) {
    t_iterator it;
    for (it = list_iterator_init(*list); !list_iterator_end(it); list_iterator_next(&it)) {
        fprintf(fout, "%d\n%.2d:%.2d:%.2d,%.3d --> %.2d:%.2d:%.2d,%.3d\n%s\n", get_indice(list_iterator_data(it)),
                get_stime_hour(list_iterator_data(it)), get_stime_min(list_iterator_data(it)),
                get_stime_sec(list_iterator_data(it)), get_stime_mil(list_iterator_data(it)),
                get_etime_hour(list_iterator_data(it)), get_etime_min(list_iterator_data(it)), get_etime_sec(list_iterator_data(it)),
                get_etime_mil(list_iterator_data(it)), get_texto(list_iterator_data(it)));
    }
    fclose(fout);
    return 1;
}

int es_close(char *texto, s_data actual) {
    if ((stack_get_init(actual) + 2) < stack_get_close(actual) && texto[stack_get_init(actual) + 1] == '/') { // </_  <-- actual+2 -  <_  <-- actual +1
        return 1;
    }

    return 0;
}

int same_tag(char *texto, int act_init, int act_close, int ant_init, int ant_close) {
    /*
    act_init    </ ....  
    act_close   ...>
    ant_init    <...
    ant_close   ...>
     */
    act_init = act_init + 2;
    ant_init++;
    while ((act_init < act_close && ant_init < ant_close) && (texto[ant_init] != ' ' && texto[act_init] != ' ')) {
        if (texto[act_init] != texto[ant_init]) // <b> .. </i>
            return 0;
        act_init++;
        ant_init++;
    }
    if (texto[act_init] == ' ' && ant_init < ant_close) return 0; // <ba> ... </b>

    if (texto[ant_init] == ' ' && act_init < act_close) return 0; // <b> .. </ba>

    return 1;
}

int clear_tag(char *texto, int act_init, int act_close, int ant_init, int ant_close, int *fin) {
    /*
     act_init    </ ....  
     act_close   ...>
     ant_init    <...
     ant_close   ...>
     */
    int i, d;
    for (i = ant_init, d = ant_close + 1; d<*fin; i++, d++) {
        texto[i] = texto[d];
    }
    int desplazamiento = ant_close - ant_init + 1;
    *fin = *fin - desplazamiento;
    act_close = act_close - desplazamiento;
    act_init = act_init - desplazamiento;
    for (i = act_init, d = act_close + 1; d<*fin; i++, d++) {
        texto[i] = texto[d];
    }
    desplazamiento = act_close - act_init + 1;
    *fin = *fin - desplazamiento;
    texto[*fin] = '\0';
    return 1;
}

void invalid_text(char *texto) {
    if(strlen(texto)>=20){
       strcpy(texto,"Subtitulo Incorrecto");
    }
    else{
        texto = realloc (texto, ( strlen(texto) + 21 ) * sizeof(char) ) ;
        strcpy(texto,"Subtitulo Incorrecto");
        texto[21]='\0';
    }
}

int verify_tag_html(char *texto, int inicio, int fin) {

    t_stack pila;
    s_data actual, anterior;
    int indice = inicio;

    stack_data_init(&actual);

    while (indice < fin || texto[indice] != '\0') {
        if ((texto[indice] == '<') && (stack_init_empty(actual))) {
            if (indice + 1 <= fin && texto[indice + 1] != ' ')stack_set_init(&actual, indice);
        }
        if ((texto[indice] == '>')&&(stack_close_empty(actual))&&(!stack_init_empty(actual))) {
            stack_set_close(&actual, indice);
        }
        if (!stack_init_empty(actual) && !stack_close_empty(actual)) {
            if (es_close(texto, actual)) {
                if (stack_empty(pila)) {
                    invalid_text(texto);
                    return 0; // error de subtitulo </> sin apertura de tag.
                } else {
                    anterior = stack_pop(&pila);
                    same_tag(texto,stack_get_init(actual),stack_get_close(actual) , stack_get_init(anterior),stack_get_close(anterior) ) ? clear_tag(texto, stack_get_init(actual), stack_get_close(actual), stack_get_init(anterior), stack_get_close(anterior),&fin) : stack_push(&pila, actual);
                    stack_data_init(&actual);
                    stack_data_init(&anterior);
                }
            } else {
                stack_push(&pila, actual);
            }
        }
        indice++;
    }
    if (!stack_data_empty(actual) && (!stack_empty(pila))) { // quedaron elementos sin matchear
        invalid_text(texto);
        return 0;
    }
    return 1; // el subtitulo es valido
}

int verify_webvtt(t_list *list) {
    t_iterator it;
    for (it = list_iterator_init(*list); !list_iterator_end(it); list_iterator_next(&it)) {
        verify_tag_html(get_texto(list_iterator_data(it)), 0, strlen(get_texto(list_iterator_data(it)))); // 0 : inicio del string ; strlen hasta donde
    }
    return 1;
}

int read_file_webvtt(FILE *fin, t_list *list) {

    char *buffer = NULL, *texto = NULL;
    ssize_t leidos = 0;
    t_data subtitle;
    size_t alocados = 10;
    int tiempo_leido, indice = 1;
    int size_texto = 0;

    if (!feof(fin)) leidos = getline(&buffer, &alocados, fin);
    if ( scanf(buffer, "WEBVTT %s") == EOF || leidos >= 0) { // mejorar
        printf("Error de formato de archivo");
        free(buffer);
        return 0;
    }
    leidos = getline(&buffer, &alocados, fin);
    if (scanf(buffer, "\n") ==EOF || leidos >= 0) {
        free(buffer);
        printf("Error de formato de archivo");
        return 0;
    }
    list_init(list);
    subtitle_init(&subtitle);
    while (!feof(fin) && leidos >= 0) {


        tiempo_leido = 0;
        while (leidos >= 0 && !tiempo_leido) {
            leidos = getline(&buffer, &alocados, fin);
            int tiempo = es_tiempo(buffer);
            if (tiempo) {
                if (tiempo == 1) {
                    set_time_hour(buffer, &subtitle);
                } else {
                    set_time(buffer, &subtitle);
                }
                tiempo_leido = 1;
            } else {
                set_label(buffer, &subtitle);
            }
        }
        if (!tiempo_leido) {
            printf("Error de estructura de archivo webvtt");
            free(buffer);
            return 0;
        }


        while (leidos >= 0) {
            leidos = getline(&buffer, &alocados, fin);
            if (*buffer == '\n' || *buffer == '\r' || leidos == -1) { // inserto en la lista,es un elemento
                set_indice(indice, &subtitle);
                set_texto(texto, &subtitle, size_texto);
                list_insert(list, copy_data(subtitle)); // insertando..
                break;
            }
            if (size_texto == 0) {
                texto = malloc((leidos + 1) * sizeof (char));
                strcpy(texto, buffer);
                size_texto = leidos;
            } else {
                size_texto = size_texto + leidos;
                texto = realloc(texto, (size_texto + 1) * sizeof (char));
                strcat(texto, buffer);

            }
        }
        free(buffer);
        buffer = NULL;
        free(texto);
        texto = NULL;
        indice++;
        size_texto = 0;

    }
    subtitle_free(&subtitle);
    return 1;
}

int main(int argc, char* argv[]) {
    wint_t test=( wint_t) argv[1][1];
    wprintf(L"%c%c", test);
    return 1;
    FILE *fin, *fout;
    t_list subtitle_input;
    int in = 0, out = 0,webvtt=0;

    if (argc <= 1) {
        printf("Faltan parametros use -help para mas ayuda");
        return 0;
    }

    /* primer pasada */
    int i;
    for (i = 1; i < argc; i++) {         
        if (!(strcmp(argv[i], "-f")) && (argc > (i + 1))) {
            if (in == 0) {
                in = 1;
                fin = fopen(argv[i + 1], "r");
                continue;
            } else {
                printf("Se enviaron 2 archivos de lectura"); //test
                if(fout) fclose(fout);
                fclose(fin);
                return 0;
            }
        }
        if (!(strcmp(argv[i], "-o")) && (argc > (i + 1))) {
            if (out == 0) {
                out = 1;
                fout = fopen(argv[i + 1], "w");
                continue;
            } else {
                printf("Se enviaron 2 archivos de salida");
                if(fin) fclose(fin);
                fclose(fout);
                return 0;
            }
        }
        if ((argv[i][0]=='-' && argv[i][1]==(char)234) && (argc > (i + 1))) {
            webvtt=1;
        }
    }
    if (!fin) {
        printf("No se pudo abrir el archivo de entrada");
        return 0;
    }
    
    if(!webvtt){
        printf("Funcionalidad del TPI");
        return 0;
    }

    for (i = 1; i < argc; i++) {
        if ((argv[i][0] == '-') && (strlen(argv[i]) == 2)) {
            switch (argv[i][1]) {
                case 'f': i++;
                    if (!read_file_webvtt(fin, &subtitle_input)) { // se encontro algun error de estructura se termina el programa
                        list_free(&subtitle_input);
                        fclose(fin);
                        return 0;
                    }
                    fclose(fin);
                    break;
                case 'v': verify_webvtt(&subtitle_input);
                    break;
                case 'm': printf("Funcionalidad del TPI");
                    break;
                case 'o': i++;
                    create_file_srt(fout, &subtitle_input);
                    break;
                case 's': printf("Funcionalidad del TPI");
                    break;
                case 'b': printf("Funcionalidad del TPI");
                    break;
                case 'd': printf("Funcionalidad del TPI");
                    break;
                case 'M': printf("Funcionalidad del TPI");
                    break;
                default: printf("Parametro invalido use -help para mas ayuda");
                    return 3;
                    break;
            }
        } else {
            printf("Parametro invalido use -help para mas ayuda");
            return 0;
        }

    }
    list_free(&subtitle_input);
    return 0;
}

