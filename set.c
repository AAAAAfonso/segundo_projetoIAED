/* 
*Ficheiro:  set.c 
*Autor: Afonso Freitas
*descrição: este ficheiro contém as funcoes associadas ao comando set
*/

#include "projeto_header.h"

void set(Directory* first_dir, char* str_array,HashValue** values){

    int i = 0,len,hash_value;
    char* value;
    Path* path ;
    Directory* dir = first_dir;
    
    /*leitura de um caminho*/
    path = readPath(str_array);
    /*leitura de um valor*/
    value = readValue(str_array);

    len=path->quant_path;
    /*associacao a de uma inteiro a uma cadeia de caracteres (valor)*/
    if((hash_value = hash(value)) == 0) hash_value = 1;

    /*adiciona a uma arvore todos os sub-caminhos por ordem de criação
    dos componentes de acordo com a profundidade*/
    for(i=0;i<len;++i){
        dir->head = insert_without_rep(dir->head,path->sub_path[i]);
        dir = insert_dir(dir,INICIAL_DEPTH,(i+1),path);
        dir = search_dir(dir,INICIAL_DEPTH,(i+1),path); 
    }

    /*remove um valor associado a uma diretoria,caso ja exista
    um valor associado a essa diretoria*/
    if(dir->hash_value != 0)
        values[dir->hash_value] = delete_hashvalue(values[dir->hash_value],dir);
    /*insere o valor numa HashTable*/
    insereHashValue(dir,value,values,hash_value);
    delete_path(path);
    path = NULL;
} 