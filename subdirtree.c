#include "projeto_header.h"

/*cria um elemento*/
subdir NEW(char* text, subdir l, subdir r) {
    subdir x = (subdir) malloc(sizeof(struct node));
    char* aux = malloc(strlen(text)*sizeof(char)+1);
    strcpy(aux,text);
    x->txt = aux;
    x->l = l;
    x->r = r;
    return x;
}

/*procura uma subdireotria*/
subdir searchSubDir(subdir h, char* text) {
    if (h == NULL)
        return NULL;
    if (strcmp(text,h->txt) == SAME_STR)
        return h;
    if (strcmp(text,h->txt) < SAME_STR)
        return searchSubDir(h->l, text);
    else
        return searchSubDir(h->r, text);
}

/*insere um elemento, caso repetido devolve NULL*/
subdir insert_without_rep(subdir h, char* text) {
    if (h == NULL)
        return NEW(text, NULL, NULL);
    if (strcmp(text,h->txt) < SAME_STR)
        h->l = insert_without_rep(h->l,text);
    else if (strcmp(text,h->txt) > SAME_STR)
        h->r = insert_without_rep(h->r,text);
    return h;
}

subdir max(subdir h) {
    while(h != NULL && h->r != NULL)
        h = h->r;
    return h;
}

/*remove uma subdiretoria da arvore*/
subdir delete_node(subdir h, char* text) {
    subdir aux ;
    if (h == NULL) return h; 
    /*procura até encontrar a cadeia de caracteres*/
    else if (strcmp(text, h->txt) < 0) h->l = delete_node(h->l,text);
    else if (strcmp(text, h->txt) > 0) h->r = delete_node(h->r,text) ;
    else {
        if (h->l != NULL && h->r != NULL ) { /*ambos os filhos existem*/
            char* x = h->txt;
            aux = max(h->l);
            h->txt = aux->txt;
            aux->txt = x;
            h->l = delete_node(h->l, aux->txt);
        }
        else {
            aux = h;
            if ( h->l == NULL && h->r == NULL ) h = NULL; /* caso não haja filhos*/
            else if (h->l == NULL) h = h->r; /* caso haja um filho na esquerda*/
            else h = h->l; /* caso haja um filho na direita*/
            free(aux->txt);
            free(aux);
        }
    }
    return h;
}