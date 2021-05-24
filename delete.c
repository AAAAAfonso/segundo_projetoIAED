/* 
*Ficheiro:  delete.c 
*Autor: Afonso Freitas
*descrição: contem as funções associadas ao comando delete
*/

#include "projeto_header.h"

/*remove da memoria todos as diretoria excepto a inicial */
void deleteEverything(Directory* first_dir,HashValue** values){
    traverse_delete_dir(first_dir->diferent,values);
    traverse_delete_sub(first_dir->head);
    first_dir->head = NULL;
    first_dir->diferent = NULL;
}

/*remove da memoria elementos com profundidade nula*/
void deleteRootEl(Directory* first_dir,Directory* aux,HashValue** values,
Path* path){
    Directory *aux_prox;
    /*remove uma subdiretoria da raiz base*/
    first_dir->head=delete_node(first_dir->head,path->sub_path[path->quant_path-1]);
    aux_prox = first_dir;
    /*precorre todas as raizes ate encontrar a pretendida*/
    while (strcmp(aux_prox->diferent->base_path->sub_path[0],path->sub_path[0]) 
    != SAME_STR)
        aux_prox = aux_prox->diferent;
    /*altera a árvore*/
    aux_prox->diferent = aux->diferent;
    /*remove as diretorias associadas*/
    traverse_delete_dir(aux->equal,values);
    delete_dir(aux,values);
}


/*remove da memória caso um elemento tenha a mesma profundidade */
void deleteSameDepth(Directory* aux,Directory* auxprox
,HashValue** values,Path* path){
    /*remove uma subdiretoria da raiz principal*/
    auxprox->head = delete_node(auxprox->head,path->sub_path[path->quant_path-1]);
    auxprox = auxprox->equal;
    /*precorre todas as raizes ate encontrar a pretendida*/
    while (strcmp(auxprox->diferent->base_path->sub_path[path->quant_path-1],
    path->sub_path[path->quant_path-1]) != SAME_STR)
        auxprox = auxprox->diferent;
    /*altera a arvore*/
    auxprox->diferent = aux->diferent;
    /*remove as diretorias associadas*/
    traverse_delete_dir(aux->equal,values);
    delete_dir(aux,values);
}

/*remove da memória caso tenham profundidades diferentes */
void deleteDifDepth(Directory* aux,Directory* auxprox
,HashValue** values,Path* path){
    auxprox->head=delete_node(auxprox->head,path->sub_path[path->quant_path-1]);
    aux = auxprox->equal;
    auxprox->equal = aux->diferent;
    traverse_delete_dir(aux->equal,values);
    delete_dir(aux,values);
}

/*função principal do comando delete*/
int delete(Directory* first_dir,char* str_array,HashValue** values){
    
    Directory *aux, *aux_prox;
    Path* path;

    /*caso não haja input termina e apaga tudo(menos a raiz)*/
    if(getchar() == '\n'){
        deleteEverything(first_dir,values);
        return OK;
    }
    path = readPath(str_array);
    if(path == NULL) return NO_MEM;

    if((aux=search_dir(first_dir,INICIAL_DEPTH,path->quant_path,path)) != NULL){
        if(aux->base_path->quant_path == 1){
            deleteRootEl(first_dir,aux,values,path);
            delete_path(path);
            path = NULL;
            return OK;
        }
        /*encontra a diretoria anterior à que será removida*/
        aux_prox = search_dir(first_dir,INICIAL_DEPTH,path->quant_path-1,path);
        if(aux_prox == NULL){
            delete_path(path);
            path = NULL;
            return NO_MEM;
        }
        
        /*caso a diretoria não esteja anterior à removida */
        if(strcmp(aux_prox->equal->base_path->sub_path[path->quant_path-1],
        path->sub_path[path->quant_path-1]) != SAME_STR)
            deleteSameDepth(aux,aux_prox,values,path);
        else
            deleteDifDepth(aux,aux_prox,values,path);
    }
    else{ 
        printf(NOT_FOUND);
    } 
    delete_path(path);
    path = NULL;
    return OK;
}