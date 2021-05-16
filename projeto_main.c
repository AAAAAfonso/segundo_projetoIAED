#include "projeto_header.h"

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

    scanf("%7s",command);
    while(strcmp(command,QUIT_STR) != 0){
        if (strcmp(command,HELP_STR) == 0){
            help();
        }
        scanf("%7s",command);
    }

    return EXIT_SUCCESS;
}