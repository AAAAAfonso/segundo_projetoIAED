/* 
*Ficheiro:  hash_table.c 
*Autor: Afonso Freitas
*descrição: contem a função associada ao comando search
*/

#include "projeto_header.h"

/**/
void search(char* str_array,HashValue** values){
    int len,check,i;
    char* value;
    Directory* aux;

    value = readValue(str_array);

    check = hash(value);
    if(check == 0) check = 1;

    if((aux = search_last(value,values,check)) == NULL) printf(NOT_FOUND);
    else{
        len = aux->base_path->quant_path;
        for(i = 0; i < len;++i)
            printf("/%s", aux->base_path->sub_path[i]);
        printf("\n");
    }
    free(value);
}