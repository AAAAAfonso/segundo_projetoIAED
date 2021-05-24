/* 
*Ficheiro:  find.c 
*Autor: Afonso Freitas
*descrição: contem a funcao principal do codigo e efetua algumas incializações
*/

#include "projeto_header.h"


/*função help*/
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

/*cria uma nova Path de acordo com uma string (nao faz a divisao por tokens)*/
Path* INITPath(char* text,int depth){
    char** res = (char**) malloc(sizeof(char*)*depth);
    Path* x= (Path*) malloc(sizeof(Path));
    res[0] = (char*) malloc(sizeof(char)*(strlen(text)+1));
    strcpy(res[0],text);
    x->sub_path = res;
    x->quant_path = depth;
    return x;
}

int main(){
    /*armazena a string de um possivel comando*/
    char command[LEN_COMAND_MAX],str_array[MAX_LINE];
    /*inicialização do tamanho de uma hash table*/
    HashValue* values[MAXIMO];
    /*inicializa a raiz principal*/
    struct dir* first_dir;
    struct path* inicial_path;
    /*maquina de estados e um inteiro auxiliar*/
    int i,status = OK ;
    inicial_path = INITPath(CARACTERHOME,1);
    first_dir = NEWDirectory(inicial_path,NULL,NULL,1);
    /*inicializa a hash table*/
    for(i=0;i<MAXIMO;++i) values[i] = NULL;


    scanf("%s",command);
    while(status == OK){
        if(strcmp(command,QUIT_STR) ==  SAME_STR){
            status = QUIT;
        }else if (strcmp(command,HELP_STR) ==  SAME_STR){
            help();
        }else if (strcmp(command,SET_STR) == SAME_STR){
            status = set(first_dir,str_array,values);
        }else if (strcmp(command,PRINT_STR) == SAME_STR){
            print(first_dir,values);
        }else if (strcmp(command,FIND_STR) == SAME_STR){
            status = find(first_dir,str_array,values);
        }else if (strcmp(command,LIST_STR) == SAME_STR){
            status = list(first_dir,str_array);
        }else if (strcmp(command,SEARCH_STR) == SAME_STR){
            status = search(str_array,values);
        }else if(strcmp(command,DELETE_STR) == SAME_STR){
            status = delete(first_dir,str_array,values);
        }
        scanf("%s",command);
    }
    if(status == NO_MEM)
        printf("No Memory");
    traverse_delete_dir(first_dir->diferent,values);
    delete_path(inicial_path);
    delete_dir(first_dir,values);
    return EXIT_SUCCESS;
}