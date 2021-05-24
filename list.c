/* 
*Ficheiro:  list.c 
*Autor: Afonso Freitas
*descrição: contem a funcao associada ao comando list
*/

#include "projeto_header.h"

/*precorre uma "binary tree" que contem as subdiretorias
por ordem alfabetica ou seja in-order*/
void traverse_alphabetic(subdir h){
    if (h == NULL)
        return;
    traverse_alphabetic(h->l);
    printf("%s\n",h->txt);
    traverse_alphabetic(h->r);
}

/* Imprime todos os componentes imediatos a um caminho
por ordem alfabética, ou seja o seu diretório, quando invocado sem argumentos,
lista os componentes da raiz. Caso nao seja encontrado nehum caminhho imprime 
"not found"*/
int list(Directory* first_dir,char* str_array){

    Path* path;

    /*caso seja chamada sem argumentos*/
    if(getchar() == '\n')
        traverse_alphabetic(first_dir->head);
    else{

        Directory* aux;
        if((path = readPath(str_array)) == NULL) return NO_MEM;
        /*travessa por ordem alfabetica uma binary tree com todas as*/
        if((aux=search_dir(first_dir,0,path->quant_path,path)) != NULL){
            traverse_alphabetic(aux->head);
        }
        else
            printf(NOT_FOUND);
        delete_path(path);
        path = NULL;
    } 
    return OK;
}