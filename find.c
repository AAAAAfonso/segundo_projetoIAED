/* 
*Ficheiro:  find.c 
*Autor: Afonso Freitas
*descrição: contem a funcao associada ao comando find
*/

#include "projeto_header.h"

/*
*Imprime o valor associado a  um dado caminho
*caso nao o seja encontrado imprime "not found", caso encontre um
*caminho mas nenhum valor associado imprime "not found"
*/
int find(Directory* first_dir,char* str_array,HashValue** values){

    Directory* aux;
    Path* path;

    if((path = readPath(str_array)) == NULL) return NO_MEM;

    /*procura através de um caminho um dado valor*/
    if((aux=search_dir(first_dir,0,path->quant_path,path)) != NULL){
        if(aux->hash_value == 0){ /*caso nao exista nenhum valor associado*/
            printf(NO_DATA);
        }
        else{                     /*imprime valor associado*/
            printf("%s\n", findByHashValue(aux,values[aux->hash_value])->value);
        }
    }
    else{                         /*caso não exista nenhum caminho associado*/
        printf(NOT_FOUND);
    }
    delete_path(path);
    path = NULL;
    return OK;
}