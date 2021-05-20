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

void traverse(Directory* h){

    if (h == NULL)
        return;
    if(h->value != NULL){
        int i;
        for(i = 0; i < h->base_path->quant_path;++i){
            printf("/%s", h->base_path->sub_path[i]);
        }
        printf(" %s\n", h->value);
    }
    traverse(h->equal);
    traverse(h->diferent);
}

void traverse_filter(Directory* h, char* value,int* check){

    if(check[0] == 0){
        if (h == NULL)
            return;
        if(h->value != NULL && strcmp(h->value,value) == SAME_STR){
            int i;
            for(i = 0; i < h->base_path->quant_path;++i){
                printf("/%s", h->base_path->sub_path[i]);
            }
            printf("\n");
            check[0]++;
        }
        traverse_filter(h->equal,value,check);
        traverse_filter(h->diferent,value,check);
    }
}

void traverse_alphabetic(link h){
    if (h == NULL)
        return;
    traverse_alphabetic(h->l);
    printf("%s\n",h->txt);
    traverse_alphabetic(h->r);
}

void traverse_delete_dir(Directory* h){
    if (h == NULL)
        return;
    traverse_delete_dir(h->equal);
    traverse_delete_dir(h->diferent);
    delete_dir(h);
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

void delete_dir(Directory* h){

    traverse_delete_sub(h->head);
    free(h->value);
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
    x->value = NULL;
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
    else if(strcmp(base->base_path->sub_path[depth],path->sub_path[depth]) != SAME_STR)
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
    else if(strcmp(base->base_path->sub_path[depth],new_path->sub_path[depth]) != SAME_STR)
        return search_dir(base->diferent,depth,max_size,new_path);   
    return base;
}  

Directory* closest(Directory* base,Caminho* objective, int depth){
    if(depth == objective->quant_path)
        return NULL;
    while (base->diferent != NULL 
    && strcmp(base->diferent->base_path->sub_path[depth],
    objective->sub_path[depth]) != 0){
        base = base->diferent;    
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