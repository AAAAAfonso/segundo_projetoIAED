/* 
*Ficheiro:  hash_table.c 
*Autor: Afonso Freitas
*descrição: contem a funções associadas à hash table
*/

#include "projeto_header.h"

/*dado uma cadeia de caracteres atribui um inteiro
que corresponderá a um inidice de uma hash table*/
int hash(char* value) { 
    int hash = 0,c,i = 0;

    while ((c = value[i++]) != 0 ) { 
        hash = (hash*33 + c)%MAXIMO; 
    }
    return hash;
}

/*procura numa linked list de umaa hash table um determinado valor*/
HashValue* findByHashValue(Directory* h, HashValue* hash_val){
    if(hash_val == NULL) /*caso o primeiro valor seja NULL devolve-lo*/
        return NULL;
    /*caso exista um único valor e esse seja igual a h*/
    if(hash_val->next == NULL){
        if(hash_val->dir != h)
            return NULL;
        return hash_val;
    }else{
        while (hash_val->dir != h) hash_val = hash_val->next;
        return hash_val;
    }
}

/*remove de uma hash tabel um determinado valor*/
HashValue* delete_hashvalue(HashValue* hash_value,Directory* h){
    HashValue* aux, *aux1 = hash_value;
    if(hash_value != NULL){
        if(hash_value->value != NULL){
            /*caso exista um unico valor remove*/
            if(hash_value->next == NULL) free(hash_value->value);
            else{
                /*caso o o primeiro valor contenha a diretoria, remove-lo*/
                if(hash_value->dir == h){
                    aux = aux1->next;
                    free(hash_value->value);
                    free(hash_value);
                    return aux;
                }
                /*senão, procura até encontrar um valor com a mesma diretoria*/
                while (hash_value->next->dir != h) hash_value = hash_value->next;
                    
                aux = hash_value->next;
                hash_value->next = hash_value->next->next;
                free(aux->value);
                free(aux);
                return aux1;
            }
        }
        free(hash_value);
    }  
    return NULL;
}

/*insere um valor no inicio da linked list associada a uma hash table*/
void insereHashValue(Directory* dir,char* value,HashValue** values,int hash_int){

    HashValue* next_el = malloc(sizeof(HashValue));

    dir->hash_value = hash_int;    
    next_el->dir = dir;   
    next_el->value = value;
    next_el->next = values[hash_int];
    values[hash_int] = next_el;
}
/*precorre a linked list e retorna a diretoria da ultima vez que
essa apareceu uma dada cadeia de caracteres*/
Directory* search_last(char* value,HashValue** values,int hash_int){
    HashValue* aux = values[hash_int];
    Directory* aux_dir = NULL;
    /*precorre a lista até ao fim, se encontrar o valor pretendido 
    adiciona a uma variavel e retorna quando terminar*/
    while(aux != NULL){
        if(aux->value != NULL && strcmp(aux->value,value) == SAME_STR)
            aux_dir = aux->dir;
        aux = aux->next;
    }
    return aux_dir;
}