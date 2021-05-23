#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_COMAND_MAX 6+1
#define SAME_STR 0

#define MAX_LINE 65535 
#define MAXIMO 74903


#define HELP_STR "help"
#define HELP_DESC "Imprime os comandos disponíveis."

#define QUIT_STR "quit"
#define QUIT_DESC "Termina o programa."

#define SET_STR "set"
#define SET_DESC "Adiciona ou modifica o valor a armazenar."

#define PRINT_STR "print"
#define PRINT_DESC "Imprime todos os caminhos e valores."

#define FIND_STR "find"
#define FIND_DESC "Imprime o valor armazenado."

#define LIST_STR "list"
#define LIST_DESC "Lista todos os componentes imediatos de um sub-caminho."

#define SEARCH_STR "search"
#define SEARCH_DESC "Procura o caminho dado um valor."

#define DELETE_STR "delete"
#define DELETE_DESC "Apaga um caminho e todos os subcaminhos."

typedef struct node* link;
typedef struct value* link_value;

typedef struct dir{
    link head;
    int hash_value;
    struct caminho* base_path;
    struct dir* equal;
    struct dir* diferent;   
} Directory;

struct node {
    char* txt;
    link l,r;
};

typedef struct caminho{
    char** sub_path;
    int quant_path;
}Caminho;

typedef struct hashvalue{
    char* value;
    struct dir* dir;
    struct hashvalue* next;
}HashValue;

HashValue* findByHashValue(Directory* h, HashValue* hash_val);
Directory* search_last(char* value,HashValue** values,int hash_int);
Directory* NEWDirectory(Caminho* path,Directory* equal,Directory* dif,int depth);
Directory* insert_dir(Directory* base,int depth,int max_size,Caminho* path);
Directory* search_dir(Directory* base,int depth,int max_size,Caminho* new_path);
Directory* closest(Directory* base,Caminho* objective, int depth);
Caminho* NEWPath(char* text,int depth);
char** leitura_comando(char* full_input,int len);
link NEW(char* txt, link l, link r);
link insert_without_rep(link h, char* text);
link max(link h);
link delete_node(link h, char* text);
link search(link h, char* text) ;
void traverse_delete_sub(link h);
void traverse(Directory* h,HashValue** values);
void traverse_alphabetic(link h);
void traverse_delete_dir(Directory* h,HashValue** values);
void delete_dir(Directory* h,HashValue** values);
void deleteTree(struct dir** h);
void delete_path(Caminho* h);
HashValue* delete_hashvalue(HashValue* hash_value,Directory* h);
void insereHashValue(Directory* dir,char* value,HashValue** values,int hash_int);
int hash(char* value);

