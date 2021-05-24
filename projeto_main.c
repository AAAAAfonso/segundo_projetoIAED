#include "projeto_header.h"

void delete_(Directory* first_dir,char* str_array,HashValue** values){
    
    Directory *aux, *aux_prox;
    Path* path;

    if(getchar() == '\n'){
        traverse_delete_dir(first_dir->diferent,values);
        traverse_delete_sub(first_dir->head);
        first_dir->head = NULL;
        first_dir->diferent = NULL;
        return;
    }
    path = readPath(str_array);

    if((aux = search_dir(first_dir,0,path->quant_path,path)) != NULL){
        if(aux->base_path->quant_path == 1){
            first_dir->head = delete_node(first_dir->head,path->sub_path[path->quant_path-1]);
            aux_prox = first_dir;
            while (strcmp(aux_prox->diferent->base_path->sub_path[0],
            path->sub_path[0]) != 0)
                aux_prox = aux_prox->diferent;
            aux_prox->diferent = aux->diferent;
            traverse_delete_dir(aux->equal,values);
            delete_dir(aux,values);
            delete_path(path);
            path = NULL;
            return;
        }
        aux_prox = search_dir(first_dir,0,path->quant_path-1,path);
        if(strcmp(aux_prox->equal->base_path->sub_path[path->quant_path-1],
        path->sub_path[path->quant_path-1]) != 0){
            aux_prox->head = delete_node(aux_prox->head,path->sub_path[path->quant_path-1]);
            aux_prox = aux_prox->equal;
            while (strcmp(aux_prox->diferent->base_path->sub_path[path->quant_path-1],
            path->sub_path[path->quant_path-1]) != 0)
                aux_prox = aux_prox->diferent;
            aux_prox->diferent = aux->diferent;
            traverse_delete_dir(aux->equal,values);
            delete_dir(aux,values);
        }
        else{
            aux_prox->head = delete_node(aux_prox->head,path->sub_path[path->quant_path-1]);
            aux = aux_prox->equal;
            aux_prox->equal = aux->diferent;
            traverse_delete_dir(aux->equal,values);
            delete_dir(aux,values);
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
    char command[LEN_COMAND_MAX],str_array[MAX_LINE];
    HashValue* values[MAXIMO];
    struct dir* first_dir;
    struct path* inicial_path;
    int i;
    for(i=0;i<MAXIMO;++i) values[i] = NULL;
    inicial_path = NEWPath(".",1);
    first_dir = NEWDirectory(inicial_path,NULL,NULL,1);

    scanf("%s",command);
    while(strcmp(command,QUIT_STR) !=  SAME_STR){
        if (strcmp(command,HELP_STR) ==  SAME_STR){
            help();
        }else if (strcmp(command,SET_STR) == SAME_STR){
            set(first_dir,str_array,values);
        }else if (strcmp(command,PRINT_STR) == SAME_STR){
            print(first_dir,values);
        }else if (strcmp(command,FIND_STR) == SAME_STR){
            find(first_dir,str_array,values);
        }else if (strcmp(command,LIST_STR) == SAME_STR){
            list(first_dir,str_array);
        }else if (strcmp(command,SEARCH_STR) == SAME_STR){
            search(str_array,values);
        }else if(strcmp(command,DELETE_STR) == SAME_STR){
            delete(first_dir,str_array,values);
        }
        scanf("%s",command);
    }
    traverse_delete_dir(first_dir->diferent,values);
    delete_path(inicial_path);
    delete_dir(first_dir,values);
    return EXIT_SUCCESS;
}