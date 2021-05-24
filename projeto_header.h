#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_COMAND_MAX 6+1
#define SAME_STR 0

#define MAX_LINE 65535 
#define MAXIMO 98317
#define INICIAL_DEPTH 0
#define TOKEN '/'
#define TOKEN_STR "/"
#define BLANKCHAR(array,ind) array[ind] == ' ' || array[ind] == '\t'||array[ind] == '\n'

#define HELP_STR "help"
#define HELP_DESC "Imprime os comandos disponíveis."

#define NO_DATA "no data\n"
#define NOT_FOUND "not found\n"

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
    struct path* base_path;
    struct dir* equal;
    struct dir* diferent;   
} Directory;

struct node {
    char* txt;
    link l,r;
};

typedef struct path{
    char** sub_path;
    int quant_path;
}Path;

typedef struct hashvalue{
    char* value;
    struct dir* dir;
    struct hashvalue* next;
}HashValue;

Path* readPath(char* str_array);
char* readValue(char* str_array);
void set(Directory* first_dir, char* str_array,HashValue** values);
void print(Directory* h,HashValue** values);
void find(Directory* first_dir,char* str_array,HashValue** values);
void list(Directory* first_dir,char* str_array);
void search(char* str_array,HashValue** values);
void delete(Directory* first_dir,char* str_array,HashValue** values);

HashValue* findByHashValue(Directory* h, HashValue* hash_val);
Directory* search_last(char* value,HashValue** values,int hash_int);
Directory* NEWDirectory(Path* path,Directory* equal,Directory* dif,int depth);
Directory* insert_dir(Directory* base,int depth,int max_size,Path* path);
Directory* search_dir(Directory* base,int depth,int max_size,Path* new_path);
Directory* closest(Directory* base,Path* objective, int depth);
Path* NEWPath(char* text,int depth);
char** leitura_comando(char* full_input,int len);
link NEW(char* txt, link l, link r);
link insert_without_rep(link h, char* text);
link max(link h);
link delete_node(link h, char* text);
link searchSubDir(link h, char* text) ;
void traverse_delete_sub(link h);
void traverse_alphabetic(link h);
void traverse_delete_dir(Directory* h,HashValue** values);
void delete_dir(Directory* h,HashValue** values);
void deleteTree(struct dir** h);
void delete_path(Path* h);
HashValue* delete_hashvalue(HashValue* hash_value,Directory* h);
void insereHashValue(Directory* dir,char* value,HashValue** values,int hash_int);
int hash(char* value);