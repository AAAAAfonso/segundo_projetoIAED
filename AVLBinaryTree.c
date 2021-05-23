#include "projeto_header.h"

link NEW(char* text, link l, link r) {
    link x = (link) malloc(sizeof(struct node));
    char* aux = malloc(strlen(text)*sizeof(char)+1);
    strcpy(aux,text);
    x->txt = aux;
    x->l = l;
    x->r = r;
    return x;
}

link search(link h, char* text) {
    if (h == NULL)
        return NULL;
    if (strcmp(text,h->txt) == SAME_STR)
        return h;
    if (strcmp(text,h->txt) < SAME_STR)
        return search(h->l, text);
    else
        return search(h->r, text);
}

link insert_without_rep(link h, char* text) {
    if (h == NULL)
        return NEW(text, NULL, NULL);
    if (strcmp(text,h->txt) < SAME_STR)
        h->l = insert_without_rep(h->l,text);
    else if (strcmp(text,h->txt) > SAME_STR)
        h->r = insert_without_rep(h->r,text);
    return h;
}

link max(link h) {
    while(h != NULL && h->r != NULL)
        h = h->r;
    return h;
}

link delete_node(link h, char* text) {
    link aux ;
    if (h == NULL) return h;
    else if (strcmp(text, h->txt) < 0) h->l = delete_node(h->l,text);
    else if (strcmp(text, h->txt) > 0) h->r = delete_node(h->r,text) ;
    else {
        if (h->l != NULL && h->r != NULL ) { /* caso 3 */
            char* x = h->txt;
            aux = max(h->l);
            h->txt = aux->txt;
            aux->txt = x;
            h->l = delete_node(h->l, aux->txt);
        }
        else {
            aux = h;
            if ( h->l == NULL && h->r == NULL ) 
                h = NULL; /* Se o nó nao tiver filhos */
            else if (h->l == NULL) 
                h = h->r; /* caso 2a */
            else 
                h = h->l; /* caso 2b */
            free(aux->txt);
            free(aux);
        }
    }
    return h;
}

HashValue* findByHashValue(Directory* h, HashValue* hash_val){
    if(hash_val == NULL)
        return NULL;
    if(hash_val->next == NULL)
        return hash_val;
    else{
        while (hash_val->dir != h){
            hash_val = hash_val->next;
        }
        return hash_val;
    }
}

void traverse(Directory* h,HashValue** values){

    int i;
    HashValue* aux;
    if (h == NULL)
        return;
    aux = findByHashValue(h, values[h->hash_value]);
    if(aux != NULL){
        for(i = 0; i < h->base_path->quant_path;++i){
            printf("/%s", h->base_path->sub_path[i]);
        }
        printf(" %s\n", aux->value);
    }
    traverse(h->equal,values);
    traverse(h->diferent,values);
}


void traverse_alphabetic(link h){
    if (h == NULL)
        return;
    traverse_alphabetic(h->l);
    printf("%s\n",h->txt);
    traverse_alphabetic(h->r);
}

void traverse_delete_dir(Directory* h,HashValue** values){
    if (h == NULL)
        return;
    traverse_delete_dir(h->equal,values);
    traverse_delete_dir(h->diferent,values);
    delete_dir(h,values);
    h = NULL;
}

void delete_sub(link h){
    free(h->txt);
    free(h);
}

void traverse_delete_sub(link h){
    if (h == NULL)
        return;
    traverse_delete_sub(h->l);
    traverse_delete_sub(h->r);
    delete_sub(h);
}


void delete_path(Caminho* h){
    int i;
    for(i = 0; i < h->quant_path;++i)
        free(h->sub_path[i]);
    free(h->sub_path);
    free(h);
}

HashValue* delete_hashvalue(HashValue* hash_value,Directory* h){
    HashValue* aux, *aux1 = hash_value;
    if(hash_value != NULL){
        if(hash_value->value != NULL){
            if(hash_value->next == NULL){
                free(hash_value->value);
            }else{
                if(hash_value->dir == h){
                    aux = aux1->next;
                    free(hash_value->value);
                    free(hash_value);
                    return aux;
                }
                while (hash_value->next->dir != h){
                    hash_value = hash_value->next;
                }
                aux = hash_value->next;
                hash_value->next = hash_value->next->next;
                free(aux->value);
                free(aux);
                return aux1;
            }
        }
        free(hash_value);
        return NULL;
    }  
    return NULL;
}

void delete_dir(Directory* h,HashValue** values){

    traverse_delete_sub(h->head);
    values[h->hash_value] = delete_hashvalue(values[h->hash_value],h);
    delete_path(h->base_path);
    free(h);  
    h = NULL;
    
}

Caminho* NEWPath(char* text,int depth){
    int i;
    char** res = (char**) malloc(sizeof(char*)*depth);
    Caminho* x=(Caminho*) malloc(sizeof(Caminho));
    for(i = 0;i<depth;i++) {
        res[i] = malloc(sizeof(char)*(strlen(text)+1));
        strcpy(res[i],text);
    }
    x->sub_path = res;
    x->quant_path = depth;
    return x;
}

Directory* NEWDirectory(Caminho* path,Directory* equal,Directory* dif,int depth){
    int j,i,len;
    char** aux = (char**) malloc(sizeof(char*)*depth);
    Directory* x = (Directory*) malloc(sizeof(struct dir));
    Caminho* new_path=(Caminho*) malloc(sizeof(Caminho));

    for(j = 0;j<depth;j++) {
        len = strlen(path->sub_path[j]);
        aux[j] = (char*) malloc(sizeof(char)*(len+1));
        for(i = 0; i < len; i++)
            aux[j][i] = path->sub_path[j][i];
        aux[j][i] = '\0';
    }
    new_path->sub_path = aux;
    new_path->quant_path = depth;
    x->base_path = new_path;
    
    x->equal = equal;
    x->diferent = dif;
    x->hash_value = 0;
    x->head = NULL;
    return x;
}

Directory* insert_dir(Directory* base,int depth,int max_size,Caminho* path){
    if(base == NULL)
        return NEWDirectory(path,NULL,NULL,max_size);
    if (base->base_path->quant_path < max_size)
        if(strcmp(base->base_path->sub_path[depth],path->sub_path[depth]) == SAME_STR)
            base->equal = insert_dir(base->equal,depth+1,max_size,path);
        else
            base->diferent = insert_dir(base->diferent,depth,max_size,path);
    else if( strcmp(base->base_path->sub_path[max_size-1],path->sub_path[max_size-1]) != SAME_STR)
        base->diferent = insert_dir(base->diferent,depth,max_size,path);
    return base;
}

Directory* search_dir(Directory* base,int depth,int max_size,Caminho* new_path){
    if(base == NULL)
        return NULL;
    if (base->base_path->quant_path < max_size)
        if(strcmp(base->base_path->sub_path[depth],new_path->sub_path[depth]) == SAME_STR)
            return search_dir(base->equal,depth+1,max_size,new_path);
        else
            return search_dir(base->diferent,depth,max_size,new_path);
    else if(strcmp(base->base_path->sub_path[max_size-1],new_path->sub_path[max_size-1]) != SAME_STR)
        return search_dir(base->diferent,depth,max_size,new_path);   
    return base;
}  

Directory* closest(Directory* base,Caminho* objective, int depth){
    if(depth == objective->quant_path)
        return NULL;
    while (base->diferent == NULL &&
    strcmp(base->diferent->base_path->sub_path[depth],
    objective->sub_path[depth]) != 0){
        base = base->diferent;
        if(base->diferent == NULL)
            return NULL;
    }
    if(depth == objective->quant_path - 1){
        return base;
    }
    base = base->diferent;
    if(depth == objective->quant_path - 2 && 
    base->equal != NULL &&
    strcmp(base->equal->base_path->sub_path[depth+1],
    objective->sub_path[depth+1]) == 0)
        return base;
    return closest(base->equal,objective, depth+1);
}

int hash(char* value) { 
    int hash = 0,c,i = 0;

    while ((c = value[i++]) != 0 ) { 
        hash = (hash*33 + c)%MAXIMO; 
    }
    return hash;
}

void insereHashValue(Directory* dir,char* value,HashValue** values,int hash_int){
    HashValue* next_el = malloc(sizeof(HashValue));
    dir->hash_value = hash_int;
    next_el->dir = dir;
    next_el->value = value;
    next_el->next = values[hash_int];
    values[hash_int] = next_el;
}

Directory* search_last(char* value,HashValue** values,int hash_int){
    HashValue* aux = values[hash_int];
    Directory* aux_dir = NULL;
    while(aux != NULL){
        if(aux->value != NULL && strcmp(aux->value,value) == SAME_STR)
            aux_dir = aux->dir;
        aux = aux->next;
    }
    return aux_dir;
}