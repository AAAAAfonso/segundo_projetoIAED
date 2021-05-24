/* 
*Ficheiro:  dirtree.c 
*Autor: Afonso Freitas
*descrição: contem as funções associadas à arvore com diretorias
*/

#include "projeto_header.h"

/*
*breve explicação:
*os elementos à "esquerda" tratados como equal são diretorias que
*representam extensões de uma dada diretoria 
*Exemplo:
*a/b tem possivel equal a/b/c
*os elementos à "direita" tratados como dif são elementos que
*numa mesma profundidade têm elementos diferentes 
*Exemplo:
*a/b tem possivel dif a/c
*/

/*
*dado uma path e um inteiro cria uma nova lista de cadeia de caracteres com a 
*os primeiros "depth" elementos de "path", e pela mesma ordem
*/
char** NEWPathAtribuition(char** aux, int depth, Path* path){
    int j,len,i;
    if(path == NULL || aux == NULL) return NULL;
    for(j = 0;j<depth;j++) {
        len = strlen(path->sub_path[j]);
        aux[j] = (char*) malloc(sizeof(char)*(len+1));
        if(aux[j] == NULL) return NULL;
        for(i = 0; i < len; i++)
            aux[j][i] = path->sub_path[j][i];
        aux[j][i] = '\0';
    }
    return aux;
}
/*adiciona uma nova diretoria*/
Directory* NEWDirectory(Path* path,Directory* equal,Directory* dif,int depth){
    char** aux = (char**) malloc(sizeof(char*)*depth);
    Path* new_path=(Path*) malloc(sizeof(Path));
    Directory* x = (Directory*) malloc(sizeof(struct dir));
    aux = NEWPathAtribuition(aux,depth,path);
    if(aux == NULL || x == NULL) return NULL;
    /*adiciona um novo path*/
    new_path->sub_path = aux;
    new_path->quant_path = depth;
    /*inicialização dos valores*/
    x->base_path = new_path;
    x->equal = equal;
    x->diferent = dif;
    x->hash_value = 0;
    x->head = NULL;
    return x;
}

/*insere uma nova diretoria à arvore*/
Directory* insert_dir(Directory* base,int depth,int max_size,Path* path){
    if(base == NULL) /*caso seja um espaço nulo*/
        return NEWDirectory(path,NULL,NULL,max_size);
    /*caso o tamanho da diretoria base seja menor que max size*/
    if (base->base_path->quant_path < max_size) 
        /*se numa profundidade os elementos são iguais aumenta a depth em 1
        e salta para o proximo elemento*/
        if(strcmp(base->base_path->sub_path[depth],
        path->sub_path[depth]) == SAME_STR) 
            base->equal = insert_dir(base->equal,depth+1,max_size,path);
        else /*caso sejam diferentes isere na próxima base diferente*/
            base->diferent = insert_dir(base->diferent,depth,max_size,path);
    /*se estão na mesma profundidade mas o sub-caminho é diferente
    tenta iserir na próxima base diferente*/
    else if(strcmp(base->base_path->sub_path[max_size-1],
    path->sub_path[max_size-1]) != SAME_STR) 
        base->diferent = insert_dir(base->diferent,depth,max_size,path);
    return base;
}

/*insere uma nova diretoria na arvore*/
Directory* search_dir(Directory* base,int depth,int max_size,Path* new_path){
    if(base == NULL) /*caso seja um espaço nulo*/
        return NULL;
    /*caso o tamanho da diretoria base seja menor que max size*/
    if (base->base_path->quant_path < max_size)
        /*se numa profundidade os elementos são iguais aumenta a depth em 1
        e procura no proximo elemento*/
        if(strcmp(base->base_path->sub_path[depth],
        new_path->sub_path[depth]) == SAME_STR)
            return search_dir(base->equal,depth+1,max_size,new_path);
        else /*caso sejam diferentes procura na próxima base diferente*/
            return search_dir(base->diferent,depth,max_size,new_path);
    /*se estão na mesma profundidade mas o sub-caminho é diferente
    tenta procurar na próxima base diferente*/        
    else if(strcmp(base->base_path->sub_path[max_size-1],
    new_path->sub_path[max_size-1]) != SAME_STR)
        return search_dir(base->diferent,depth,max_size,new_path);   
    return base; /*retorna a base porque é igual*/
}  