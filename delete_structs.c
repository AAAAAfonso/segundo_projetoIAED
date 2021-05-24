/* 
*Ficheiro:  delete_structs.c 
*Autor: Afonso Freitas
*descrição: este ficheiro contem funcoes que removem estruturas em especifico
*/

#include "projeto_header.h"

/*esta função atravessa todos os elementos usando a travesia 
post-order e remove cada uma das diretorias individualmente*/
void traverse_delete_dir(Directory* h,HashValue** values){
    if (h == NULL)
        return;
    traverse_delete_dir(h->equal,values);
    traverse_delete_dir(h->diferent,values);
    delete_dir(h,values);
    h = NULL;
}

/*remove uma sub-diretoria*/
void delete_sub(subdir h){
    free(h->txt);
    free(h);
}

/*esta função atravessa todos os elementos usando a travesia 
post-order e remove cada uma das subdiretorias individualmente*/
void traverse_delete_sub(subdir h){
    if (h == NULL)
        return;
    traverse_delete_sub(h->l);
    traverse_delete_sub(h->r);
    delete_sub(h);
}

/*remove um caminho*/
void delete_path(Path* h){
    int i;
    /*remove todos os sub caminhos*/
    for(i = 0; i < h->quant_path;++i)
        free(h->sub_path[i]);
    free(h->sub_path);
    free(h);
}

/*remove uma diretoria*/
void delete_dir(Directory* h,HashValue** values){

    /*remove todos elementos da subdiretoria*/
    traverse_delete_sub(h->head);
    /*remove o valor na hash table*/
    values[h->hash_value] = delete_hashvalue(values[h->hash_value],h);
    /*remove o caminho*/
    delete_path(h->base_path);
    free(h);  
    h = NULL;
    
}