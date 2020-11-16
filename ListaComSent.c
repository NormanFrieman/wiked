#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ListaComSent.h"
#include "Wiked_v1.h"

typedef struct cel Celula;

struct cel{
    Celula *prox;
    void *item;
};

struct lista{
    Celula *Prim;
    Celula *Ult;
};

Lista* initLista(void){
    Lista *novaLista = (Lista *)malloc(sizeof(Lista));

    novaLista->Prim = NULL;
    novaLista->Ult = NULL;

    return novaLista;
}

// ============== Funcoes responsaveis da lista de Editores ==============
void insereLista(Lista *lista, char *palavra){
    Celula *novaCelula = (Celula *)malloc(sizeof(Celula));

    novaCelula->item = strdup(palavra);
    novaCelula->prox = NULL;

    if(lista->Prim == NULL){
        lista->Prim = novaCelula;
        lista->Ult = novaCelula;
    }else{
        lista->Ult->prox = novaCelula;
        lista->Ult = novaCelula;
    }
}

void retiraLista(Lista *lista, char *palavra){
    Celula *ant = NULL, *p = lista->Prim;
    
    while(p != NULL && strcmp(p->item, palavra) != 0){
        ant = p;
        p = p->prox;
    }
    
    if(p == NULL){
        return;
    }

    if(lista->Prim == p && lista->Ult == p){
        lista->Prim = NULL;
        lista->Ult = NULL;
    }else if(lista->Prim == p){
        lista->Prim = lista->Prim->prox;
    }else if(lista->Ult == p){
        ant->prox = NULL;
        lista->Ult = ant;
    }else{
        ant->prox = p->prox;
    }
    
    free(p->item);
    free(p);
}

void imprimeLista(Lista *lista){
    Celula *p;

    for(p = lista->Prim; p != NULL; p = p->prox){
        printf("%s\n", (char *)p->item);
    }
}

void destroiLista(Lista *lista){
    Celula *p = lista->Prim;
    Celula *aux;

    while(p != NULL){
        aux = p->prox;
        free(p->item);
        free(p);
        p = aux;
    }

    free(lista);
}

// ============== Funcoes responsaveis da lista de Artigos ==============
void insereVoid(Lista *lista, void *item){
    Celula *cel = (Celula *)malloc(sizeof(Celula));

    cel->item = item;
    cel->prox = NULL;

    if(lista->Prim == NULL && lista->Ult == NULL){
        lista->Prim = cel;
        lista->Ult = cel;
        return;
    }
    
    lista->Ult->prox = cel;
    lista->Ult = cel;
}

int retiraVoid(Lista *lista, char *nome){
    Celula *p = lista->Prim;
    Celula *ant = NULL;
    
    if(lista->Prim == NULL && lista->Ult == NULL){
        return 0;
    }
    
    while(p != NULL){
        if(strcmp(retornaNome(p->item), nome) != 0){
            ant = p;
            p = p->prox;
        }else{
            break;
        }
    }

    if(p == NULL){
        return 0;
    }

    if(p == lista->Prim && p == lista->Ult){
        lista->Prim = NULL;
        lista->Ult = NULL;
    }else if(p == lista->Prim){
        lista->Prim = lista->Prim->prox;
    }else if(p == lista->Ult){
        ant->prox = NULL;
        lista->Ult = ant;
    }else{
        ant->prox = p->prox;
    }

    free(p);

    return 1;
}

// funcao auxiliar para inserir uma nova contribuicao
void* retornaVoid(Lista *lista, char *nome){
    Celula *p;
    p = lista->Prim;

    if(lista->Prim == NULL && lista->Ult == NULL){
        return NULL;
    }

    while(p != NULL){
        if(strcmp(retornaNome(p->item), nome) != 0){
            p = p->prox;
        }else{
            break;
        }
    }

    if(p == NULL){
        return NULL;
    }

    return p->item;
}
void* retornaPorInt(Lista *lista, int ind){
    Celula *p;
    p = lista->Prim;
    int aux = 0;

    if(lista->Prim == NULL && lista->Ult == NULL){
        return NULL;
    }

    while(p != NULL && aux < ind){
        p = p->prox;
        aux++;
    }

    if(p == NULL){
        return NULL;
    }

    return p->item;
}
/*
void insereContribuicao(Lista *lista, char *nomeContribuidor, char *tituloContribuicao, char *contribuicao);

void retiraContribucao(Lista *lista, char *nome, char *nomeContribuidor, char *tituloContribuicao);

void insereLink(Lista *lista, char *nomeOrigem, char *nomeDestino);

void retiraLink(Lista *lista, char *nomeOrigem, char *nomeDestino);

void caminho(Lista *lista, char *nomeOrigem, char *nomeDestino);

void imprimePagina(Lista *lista, char *nome);

void imprimeWided(Lista *lista);*/



// ============== Funcoes AUXILIARES ==============
void imprimeVoid(Lista *lista){
    Celula *p;

    for(p = lista->Prim; p != NULL; p = p->prox){
        printf("%s\n", retornaNome(p->item));
    }
}

void destroiVoid(Lista *lista){
    Celula *p = lista->Prim;
    Celula *aux = NULL;

    while(p != NULL){
        aux = p->prox;
        destroiUnitario(p->item);
        free(p);
        p = aux;
    }
    
    free(lista);
}

void destroiListasSecundarias(Lista *lista, int code){
    Celula *p = lista->Prim;
    Celula *aux = NULL;

    while(p != NULL){
        aux = p->prox;
        if(code == 0){
            destroiContrib(p->item);
        }else if(code == 1){
            destroiHist(p->item);
        }else{
            destroiLink(p->item);
        }
        free(p->item);
        free(p);
        p = aux;
    }
}