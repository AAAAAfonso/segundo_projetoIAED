/* 
*Ficheiro:  search.c 
*Autor: Afonso Freitas
*descrição: contém a função associada ao comando search
*/

#include "projeto_header.h"

/*
*Imprime o primeiro caminho encontrado que contém exatamente o <valor> indicado
*/
int search(char* str_array,HashValue** values){
    int len,check,i;
    char* value;
    Directory* aux;

    if((value = readValue(str_array)) == NULL) return NO_MEM;

    check = hash(value);
    if(check == NOVALUE) check = NEWVALUE;

    if((aux = search_last(value,values,check)) == NULL) printf(NOT_FOUND);
    else{
        len = aux->base_path->quant_path;
        for(i = 0; i < len;++i)
            printf("/%s", aux->base_path->sub_path[i]);
        printf("\n");
    }
    free(value);
    return OK;
}