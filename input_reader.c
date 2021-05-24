
/* 
*Ficheiro:  set.c 
*Autor: Afonso Freitas
*descrição: contem as funcoes que são executadas na leitura do input
*/
#include "projeto_header.h"


/* Esta função conta a quantidade de cadeias de
caracteres separadas por um caractere existente numa
numa dada cadeia*/
int countCharInStr(char* str, char token,int len){
    int status = 0,count_char = 1,i;

    for(i = 0; i < len; ++i){
        if(str[i] != token)
            status = 1;
        if(str[i] == token && status == 1){
            ++count_char;
            status = 0;
        }
    }
    return status != 0 ? count_char : --count_char;
}

/* Esta função cria a partir de um input do tipo
cadeia de caracteres um elemento da estrutura "Path" (Caminho)
essa estrutura apresenta a quantidade de sub-caminhos existentes nesse
Caminho e uma lista de cadeias de caracteres a representar esse mesmo Caminho
os sub-caminhos são separados por um token*/
Path* transformIntoPath(char* str_array,int len){

    /*Alocação de memoria para o tipo*/
    Path* path_aux = malloc(sizeof(Path));
    char** total;
    int count_char = 1,i;

    count_char = countCharInStr(str_array, TOKEN,len);
    /*caso nao seja encontrado nenhum sub-camimho sai da funcao*/
    if(count_char == 0){
        path_aux->quant_path=0;
        return path_aux;
    }
    /*aloca a quantidade necessaria e atribui a uma lista de cadeia
    de caracteres os sub-caminhos*/
    total = (char**) malloc((count_char)*sizeof(char*));
    str_array = strtok(str_array , TOKEN_STR);
    for(i = 0; i < count_char; i++) {
        total[i] = (char*)malloc((strlen(str_array)+1)*sizeof(char));
        strcpy(total[i],str_array);
        str_array = strtok(NULL, TOKEN_STR);
    }
    path_aux->sub_path=total;
    path_aux->quant_path=count_char;
    return path_aux;
}

/* Esta função retira os espacos brancos no final 
de uma determinada cadeia de caracteres e alloca 
em memoria a nova cadeia de caracteres, já transformada*/
char* transformIntoValue(char* str_array, int len){
    int i, last_espaces = 0;
    char* value;

    for(i = 0; i < len; ++i){
        /*se for encontrado um caracter branco aumenta em 1 o contador
        caso contrario reinicializa o contador a zero*/
        if(BLANKCHAR(str_array,i))
            last_espaces++;
        else  
            last_espaces = 0;
    }
    len = len-last_espaces;
    value = malloc(sizeof(char)*(len+1));
    for(i = 0; i < len; i++)
        value[i] = str_array[i];
    value[i] = '\0';
    return value;
}

/*leitura do input, sabendo que é um caminho*/
Path* readPath(char* str_array){
    scanf(" %s", str_array);
    return transformIntoPath(str_array,strlen(str_array));
}

/*leitura do input, sabendo que é um valor*/
char* readValue(char* str_array){
    scanf(" %[^\n]",str_array);
    return transformIntoValue(str_array,strlen(str_array));
}