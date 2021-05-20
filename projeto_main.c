#include "projeto_header.h"

Caminho* leitura_caminho(char* str_array,int len){
    Caminho* path = malloc(sizeof(Caminho));
    char** total;
    int status = 0,count_char = 1,i;
    /*path->quant_path = malloc(sizeof(int));*/

    for(i = 0; i < len; ++i){
        if(str_array[i] != '/')
            status = 1;
        if(str_array[i] == '/' && status == 1){
            ++count_char;
            status = 0;
        }
    }
    if(status == 0){
        --count_char;
        if(count_char == 0){
            path->quant_path=0;
            return path;
        }
    }
    total = (char**) malloc((count_char)*sizeof(char*));
    str_array = strtok(str_array , "/");
    for(i = 0; i < count_char; i++) {
        total[i] = malloc((strlen(str_array)+1)*sizeof(char));
        strcpy(total[i],str_array);
        str_array = strtok(NULL, "/");
    }
    path->sub_path=total;
    path->quant_path=count_char;
    return path;
}

char* leitura_valor(char* str_array, int len){
    int i, last_espaces = 0;
    char* valor;
    len = strlen(str_array);
    for(i = 0; i < len; ++i){
        if(str_array[i] == ' ' ||str_array[i] == '\t'||
        str_array[i] == '\n' )
            last_espaces++;
        else{
            last_espaces = 0;
        }
    }
    len = len-last_espaces;
    valor = malloc(sizeof(char)*(len+1));
    for(i = 0; i < len; i++)
        valor[i] = str_array[i];
    valor[i] = '\0';
    return valor;
}


void set(Directory* first_dir, char* str_array){

    int i = 0,len;
    char* valor;
    Caminho* path ;
    Directory* aux_bucket = first_dir;
    
    scanf(" %s", str_array);
    len = strlen(str_array);
    path = leitura_caminho(str_array,len);
    

    scanf(" %[^\n]",str_array);
    len = strlen(str_array);
    valor = leitura_valor(str_array,len);
    len=path->quant_path;

    for(i=0;i<len;++i){
        aux_bucket->head = insert_without_rep(aux_bucket->head,path->sub_path[i]);
        first_dir = insert_dir(first_dir,0,(i+1),path);
        aux_bucket = search_dir(first_dir,0,(i+1),path); 
    }
    if(aux_bucket->value != NULL){
        free(aux_bucket->value);
        aux_bucket->value = valor;
    }else{
        aux_bucket->value = valor;
    }
    delete_path(path);
    path = NULL;
} 


void print_fun(Directory* first_dir){
    traverse(first_dir);   
}

void find(Directory* first_dir,char* str_array){
    Directory* aux;
    int len;
    Caminho* path;

    scanf(" %s", str_array);
    len = strlen(str_array);
    path = leitura_caminho(str_array,len);

    if((aux=search_dir(first_dir,0,path->quant_path,path)) != NULL){
        if(aux->value == NULL){
            printf("no data\n");
        }else{
            printf("%s\n", aux->value);
        }
    }else{ 
        printf("not found\n");
    }
    delete_path(path);
    path = NULL;
}

void list(Directory* first_dir,char* str_array){

    Caminho* path;

    if(getchar() == '\n')
        traverse_alphabetic(first_dir->head);
    else{
        int len;
        Directory* aux;

        scanf(" %s", str_array);
        len = strlen(str_array);
        path = leitura_caminho(str_array,len);

        if((aux=search_dir(first_dir,0,path->quant_path,path)) != NULL){
            traverse_alphabetic(aux->head);
        }
        else
            printf("not found\n");
        delete_path(path);
        path = NULL;
    } 
}

void searchf(Directory* first_dir, char* str_array){
    int len,check[1] = {0};
    char* value;


    scanf(" %[^\n]",str_array);
    len = strlen(str_array);
    value = leitura_valor(str_array,len);

    traverse_filter(first_dir, value,check);
    if(check[0] == 0)
        printf("not found\n");

    free(value);
    
}

void delete_(Directory* first_dir,char* str_array){
    Directory *aux, *aux_prox;
    int len;
    Caminho* path;

    if(getchar() == '\n'){
        traverse_delete_dir(first_dir->diferent);
        first_dir->diferent = NULL;
        return;
    }
    scanf(" %s", str_array);
    len = strlen(str_array);
    path = leitura_caminho(str_array,len);
    if((aux_prox = closest(first_dir,path, 0)) != NULL){
        if(aux_prox->base_path->quant_path == path->quant_path){
            aux = aux_prox->diferent;
            aux->diferent = aux_prox->diferent;
            traverse_delete_dir(aux->equal);
            delete_dir(aux);
            aux_prox = search_dir(first_dir,0,path->quant_path - 1,path);
            aux_prox->head = delete_node(aux_prox->head,path->sub_path[path->quant_path-1]);
        }
        else{
            aux_prox->head = delete_node(aux_prox->head,path->sub_path[path->quant_path-1]);
            aux = aux_prox->equal;
            aux_prox->equal = aux->diferent;
            traverse_delete_dir(aux->equal);
            delete_dir(aux);
        }
    }
    else{ 
        printf("not found\n");
    } 
    delete_path(path);
    path = NULL;
}

void help(){
    printf(HELP_STR ": " HELP_DESC "\n"
        QUIT_STR ": " QUIT_DESC "\n"
        SET_STR ": " SET_DESC "\n"
        PRINT_STR ": " PRINT_DESC "\n"
        FIND_STR ": " FIND_DESC "\n"
        LIST_STR ": " LIST_DESC "\n"
        SEARCH_STR ": " SEARCH_DESC "\n"
        DELETE_STR ": " DELETE_DESC "\n");
}


int main(){
    /*armazena a string de um possivel comando*/
    char command[LEN_COMAND_MAX];
    char str_array[MAX_LINE];
    struct dir* first_dir;
    struct caminho* inicial_path;
    inicial_path = NEWPath(".",1);


    first_dir = NEWDirectory(inicial_path,NULL,NULL,1);

    scanf("%s",command);
    while(strcmp(command,QUIT_STR) !=  SAME_STR){
        if (strcmp(command,HELP_STR) ==  SAME_STR){
            help();
        }else if (strcmp(command,SET_STR) == SAME_STR){
            set(first_dir,str_array);
        }else if (strcmp(command,PRINT_STR) == SAME_STR){
            print_fun(first_dir);
        }else if (strcmp(command,FIND_STR) == SAME_STR){
            find(first_dir,str_array);
        }else if (strcmp(command,LIST_STR) == SAME_STR){
            list(first_dir,str_array);
        }else if (strcmp(command,SEARCH_STR) == SAME_STR){
            searchf(first_dir,str_array);
        }else if(strcmp(command,DELETE_STR) == SAME_STR){
            delete_(first_dir,str_array);
        }
        scanf("%s",command);
    }
    traverse_delete_dir(first_dir->diferent);
    delete_path(inicial_path);
    delete_dir(first_dir);
    return EXIT_SUCCESS;
}