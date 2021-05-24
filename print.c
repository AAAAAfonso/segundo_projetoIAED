/* 
*Ficheiro:  print.c 
*Autor: Afonso Freitas
*descrição: contem as funcoes associadas ao comando print
*/

#include "projeto_header.h"

/*responsavel por imprimir os caminhos com a formatção pedida*/
void print_aux(Directory* h,HashValue** values){
    int i;
    HashValue* aux;
    aux = findByHashValue(h, values[h->hash_value]);
    if(aux != NULL){
        for(i = 0; i < h->base_path->quant_path;++i){
            printf("/%s", h->base_path->sub_path[i]);
        }
        printf(" %s\n", aux->value);
    }
}

/*Esta função precorre a tabela pela ordem de criação, mais especificamente
usando a travessia pre-order*/
void print(Directory* h,HashValue** values){
    if(h == NULL)
        return;
    print_aux(h,values);
    print(h->equal,values);
    print(h->diferent,values);
}