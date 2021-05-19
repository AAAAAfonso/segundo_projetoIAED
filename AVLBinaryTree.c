#include "projeto_header.h"

link NEW(char* text, link l, link r) {
    link x = (link) malloc(sizeof(struct node));
    x->txt = text;
    x->nextdir = NULL;
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
        free(h->txt);
        free(aux);
        }
    }
    return h;
}

void traverse(Directory* h){

    if (h == NULL)
        return;
    if(h->valor != NULL){
        int i;
        for(i = 0; i < h->base_path->quant_path[0];++i){
            printf("/%s", h->base_path->sub_path[i]);
        }
        printf(" %s\n", h->valor->valor_txt);
    }
    traverse(h->equal);
    traverse(h->diferent);
}

link_value NEW_Value(char* text,Directory* subdir, link_value l, link_value r) {
    if(subdir->valor != NULL){
        free(subdir->valor->valor_txt);
        subdir->valor->valor_txt = text;
        return subdir->valor;
        
    }else{
        link_value x = (link_value) malloc(sizeof(struct value));
        x->valor_txt = text;
        x->origin = subdir;
        subdir->valor = x;
        x->l = l;
        x->r = r;
        return x;
    }
}

link_value insertValue(link_value base,Directory* h, char* text) {
    if (base == NULL)
        return NEW_Value(text,h, NULL, NULL);
    if (strcmp(text,base->valor_txt) <= SAME_STR)
        base->l = insertValue(base->l,h,text);
    else
        base->r = insertValue(base->r,h,text);
    return base;
}

Directory* NEWDirectory(Caminho* path,Directory* equal,Directory* dif,int depth){
    int j = path->quant_path[0];
    Directory* x = (Directory*) malloc(sizeof(struct dir));
    Caminho* new_path;

    if(depth != j){
        new_path = (Caminho*) malloc(sizeof(Caminho));
        new_path->sub_path = (char**) malloc(sizeof(char*)*(depth+1));
        new_path->quant_path = malloc(sizeof(int));
        for(j = 0;j<depth;j++)  new_path->sub_path[j] = path->sub_path[j];
        new_path->quant_path[0] = depth;
        x->base_path = new_path;
    }else{
        x->base_path = path;
    }
    x->equal = equal;
    x->diferent = dif;
    x->valor = NULL;
    x->head = NULL;
    return x;
}

Directory* insert_dir(Directory* base,int depth,int max_size,Caminho* path){
    if(base == NULL)
        return NEWDirectory(path,NULL,NULL,max_size);
    if (base->base_path->quant_path[0] < max_size)
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
    if (base->base_path->quant_path[0] < max_size)
        if(strcmp(base->base_path->sub_path[depth],new_path->sub_path[depth]) == SAME_STR)
            return search_dir(base->equal,depth+1,max_size,new_path);
        else
            return search_dir(base->diferent,depth,max_size,new_path);
    else if(strcmp(base->base_path->sub_path[depth],new_path->sub_path[depth]) != SAME_STR)
        return search_dir(base->diferent,depth,max_size,new_path);   
    return base;
}  