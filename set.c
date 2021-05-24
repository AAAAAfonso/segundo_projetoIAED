/* 
*Ficheiro:  set.c 
*Autor: Afonso Freitas
*descrição: este ficheiro contém as funções associadas ao comando set
*/

#include "projeto_header.h"

/*adiciona uma nova diretoria ao sistema*/
int set(Directory* first_dir, char* str_array,HashValue** values){

    int i = 0,len,hash_value;
    char* value;
    Path* path ;
    Directory* dir = first_dir;
    
    /*leitura de um caminho*/
    if((path = readPath(str_array))== NULL) return NO_MEM;
    /*leitura de um valor*/
    value = readValue(str_array);

    len=path->quant_path;

    /*associacao a de uma inteiro a uma cadeia de caracteres (valor)*/
    if((hash_value = hash(value)) == NOVALUE) hash_value = NEWVALUE;

    /*adiciona a uma arvore todos os sub-caminhos por ordem de criação
    dos componentes de acordo com a profundidade*/
    for(i=0;i<len;++i){
        dir->head = insert_without_rep(dir->head,path->sub_path[i]);
        dir = insert_dir(dir,INICIAL_DEPTH,(i+1),path);
        dir = search_dir(dir,INICIAL_DEPTH,(i+1),path);
        if(dir== NULL) return NO_MEM;
    }

    /*remove um valor associado a uma diretoria,caso ja exista
    um valor associado a essa diretoria*/
    if(dir->hash_value != 0)
        values[dir->hash_value] = delete_hashvalue(values[dir->hash_value],dir);
    /*insere o valor numa HashTable*/
    insereHashValue(dir,value,values,hash_value);
    if(values[dir->hash_value] == NULL) return NO_MEM;
    delete_path(path);
    path = NULL;
    return OK;
} 