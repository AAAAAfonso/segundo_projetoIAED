#include "projeto_header.h"


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

void print(Directory* h,HashValue** values){
    if(h == NULL)
        return;
    print_aux(h,values);
    print(h->equal,values);
    print(h->diferent,values);
}