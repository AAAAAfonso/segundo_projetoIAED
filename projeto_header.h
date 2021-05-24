/* 
*Ficheiro:  projeto_header.h 
*Autor: Afonso Freitas
*descrição: header do projeto
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*mesma diretoria*/
#define LEN_COMAND_MAX 6+1
#define SAME_STR 0
/*tamanho maximo do input*/
#define MAX_LINE 65535 
/*tamanho maximo da hash table*/
#define MAXIMO 98317
#define INICIAL_DEPTH 0
/*token de separção*/
#define TOKEN '/'
#define TOKEN_STR "/"
/*verifica se existe uma nova diretoria*/
#define BLANKCHAR(array,ind) array[ind] == ' ' || array[ind] == '\t'||array[ind] == '\n'
/*inteiros permitidos e nao para valores*/
#define NOVALUE 0
#define NEWVALUE 1
/*strings associadas ao comando help*/
#define HELP_STR "help"
#define HELP_DESC "Imprime os comandos disponíveis."
/*possiveis erros*/
#define NO_DATA "no data\n"
#define NOT_FOUND "not found\n"
/*strings associadas ao comando quit*/
#define QUIT_STR "quit"
#define QUIT_DESC "Termina o programa."
/*strings associadas ao comando set*/
#define SET_STR "set"
#define SET_DESC "Adiciona ou modifica o valor a armazenar."
/*strings associadas ao comando print*/
#define PRINT_STR "print"
#define PRINT_DESC "Imprime todos os caminhos e valores."
/*strings associadas ao comando find*/
#define FIND_STR "find"
#define FIND_DESC "Imprime o valor armazenado."
/*strings associadas ao comando list*/
#define LIST_STR "list"
#define LIST_DESC "Lista todos os componentes imediatos de um sub-caminho."
/*strings associadas ao comando search*/
#define SEARCH_STR "search"
#define SEARCH_DESC "Procura o caminho dado um valor."
/*strings associadas ao comando delete*/
#define DELETE_STR "delete"
#define DELETE_DESC "Apaga um caminho e todos os subcaminhos."
/*strings associadas ao comando delete*/
#define CARACTERHOME "."
/*Máquina de estados*/
#define OK 0
#define NO_MEM 1
#define QUIT 2

typedef struct node* subdir;

/*estrutura de uma diretoria*/
typedef struct dir{
    subdir head; /*ponteiro para uma arvore com subdiretorias*/
    int hash_value; /*inteiro que representa um indice numa hash table*/
    struct path* base_path; /*pointeiro para um caminho*/
    struct dir* equal;  /*explicado no ficheiro dirtree*/
    struct dir* diferent;  /*explicado no ficheiro dirtree*/
} Directory;

struct node {
    char* txt; /*ponteiro para uma cadeia de caracteres*/
    subdir l,r; /*l-menor alfabetico r-maior alfabetico*/
};

typedef struct path{
    char** sub_path; /*array de strings com ps subcaminhos*/
    int quant_path; /*quantidade de sub strings*/
}Path;

/*itens de uma hash table*/
typedef struct hashvalue{
    char* value; /*ponteiro para uma string que representa um valor*/
    struct dir* dir; /*ponteiro para uma diretoria*/
    struct hashvalue* next; /*ponteiro para um possivel*/
}HashValue;

/*funcoes principais*/
Path* readPath(char* str_array);
char* readValue(char* str_array);
int set(Directory* first_dir, char* str_array,HashValue** values);
void print(Directory* h,HashValue** values);
int find(Directory* first_dir,char* str_array,HashValue** values);
int list(Directory* first_dir,char* str_array);
int search(char* str_array,HashValue** values);
int delete(Directory* first_dir,char* str_array,HashValue** values);

/*funcoes auxiliares para a estrutura*/
Directory* search_last(char* value,HashValue** values,int hash_int);
Directory* NEWDirectory(Path* path,Directory* equal,Directory* dif,int depth);
Directory* insert_dir(Directory* base,int depth,int max_size,Path* path);
Directory* search_dir(Directory* base,int depth,int max_size,Path* new_path);
Directory* closest(Directory* base,Path* objective, int depth);
Path* INITPath(char* text,int depth);
char** leitura_comando(char* full_input,int len);
subdir NEW(char* txt, subdir l, subdir r);
subdir insert_without_rep(subdir h, char* text);
subdir max(subdir h);
subdir delete_node(subdir h, char* text);
subdir searchSubDir(subdir h, char* text) ;
void traverse_delete_sub(subdir h);
void traverse_alphabetic(subdir h);
void traverse_delete_dir(Directory* h,HashValue** values);
void delete_dir(Directory* h,HashValue** values);
void deleteTree(struct dir** h);
void delete_path(Path* h);
HashValue* findByHashValue(Directory* h, HashValue* hash_val);
HashValue* delete_hashvalue(HashValue* hash_value,Directory* h);
void insereHashValue(Directory* dir,char* value,HashValue** values,int hash_int);
int hash(char* value);