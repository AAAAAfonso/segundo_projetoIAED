#include "projeto_header.h"

Caminho* leitura_caminho(char* str_array,int len){
    Caminho* path = malloc(sizeof(Caminho));
    char** total;
    int status,count_char = 1,i;

    path->quant_path = malloc(sizeof(int));

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
            path->quant_path[0]=0;
            return path;
        }
    }
    total = (char**) malloc((count_char)*sizeof(char*));
    str_array = strtok(str_array , "/");
    for(i = 0; i < count_char; i++) {
        total[i] = malloc(strlen(str_array)*sizeof(char));
        strcpy(total[i],str_array);
        str_array = strtok(NULL, "/");
    }
    path->sub_path=total;
    path->quant_path[0] =count_char;
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
    valor = malloc(sizeof(char)*len);
    for(i = 0; i < len; i++)
        valor[i] = str_array[i];
    valor[i] = str_array[i];
    valor[i] = '\0';
    return valor;
}


void set(FLdir* dlist, char* str_array,link_value first_value ){

    int i = 0,len;
    char* valor;
    Caminho* path;
    Directory* aux_bucket = dlist->first;
    
    scanf(" %s", str_array);
    len = strlen(str_array);
    path = leitura_caminho(str_array,len);
    

    scanf(" %[^\n]",str_array);
    len = strlen(str_array);
    valor = leitura_valor(str_array,len);
    len=path->quant_path[0];

    for(i=0;i<len;++i){
        aux_bucket->head = insert_without_rep(aux_bucket->head,path->sub_path[i]);
        dlist->first = insert_dir(dlist->first,0,(i+1),path);   
    }
    aux_bucket = search_dir(dlist->first,0,i,path);
    first_value = insertValue(first_value,aux_bucket, valor);
} 


void print_fun(FLdir* dlist){
    traverse(dlist->first);   
}

void find(FLdir* dlist,char* str_array){
    Directory* aux;
    int len;
    Caminho* path;

    scanf(" %s", str_array);
    len = strlen(str_array);
    path = leitura_caminho(str_array,len);

    if((aux=search_dir(dlist->first,0,path->quant_path[0],path)) != NULL){
        if(aux->valor == NULL){
            printf("no data\n");
        }else{
            printf("%s\n", aux->valor->valor_txt);
        }
    }else{ 
        printf("not found\n");
    }
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
    char home_char[2] = "";
    
    link header = NULL;
    link_value first_value = NULL;
    char str_array[MAX_LINE];


    Directory* home = malloc(sizeof(Directory));
    FLdir* dlist = malloc(sizeof(FLdir));
    Caminho* base = (Caminho*) malloc(sizeof(Caminho));

    base->sub_path = malloc(sizeof(char*));
    base->sub_path[0] = malloc(sizeof(char)*2);
    base->quant_path = malloc(sizeof(int));
    strcpy(base->sub_path[0],home_char);
    base->quant_path[0] = 1;

    dlist->first = home;
    dlist->last = home;
    home->base_path = base;
    home->head = header;

    scanf("%s",command);
    while(strcmp(command,QUIT_STR) !=  SAME_STR){
        if (strcmp(command,HELP_STR) ==  SAME_STR){
            help();
        }else if (strcmp(command,SET_STR) == SAME_STR){
            set(dlist,str_array,first_value);
        }else if (strcmp(command,PRINT_STR) == SAME_STR){
            print_fun(dlist);
        }else if (strcmp(command,FIND_STR) == SAME_STR){
            find(dlist,str_array);
        }
        scanf("%s",command);
    }
    return EXIT_SUCCESS;
}