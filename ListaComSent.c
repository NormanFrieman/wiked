#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ListaComSent.h"

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
void insereEditor(Lista *lista, char *nomeEditor){
    Celula *novaCelula = (Celula *)malloc(sizeof(Celula));

    novaCelula->item = strdup(nomeEditor);
    novaCelula->prox = NULL;

    if(lista->Prim == NULL){
        lista->Prim = novaCelula;
        lista->Ult = novaCelula;
    }else{
        lista->Ult->prox = novaCelula;
        lista->Ult = novaCelula;
    }
}

void retiraEditor(Lista *lista, char *nomeEditor){
    Celula *ant = NULL, *p = lista->Prim;
    
    while(p != NULL && strcmp(p->item, nomeEditor) != 0){
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
        lista->Ult = ant;
    }else{
        ant->prox = p->prox;
    }

    free(p->item);
    free(p);
}

void imprimeEditores(Lista *lista){
    Celula *p;

    printf("EDITORES:\n");
    for(p = lista->Prim; p != NULL; p = p->prox){
        printf("%s\n", (char *)p->item);
    }
}

void destroiEditores(Lista *lista){
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
void inserePagina(Lista *lista, char *nome, char *outfile);

void retiraPagina(Lista *lista, char *nome);

void insereContribuicao(Lista *lista, char *nomeContribuidor, char *tituloContribuicao, char *contribuicao);

void retiraContribucao(Lista *lista, char *nome, char *nomeContribuidor, char *tituloContribuicao);

void insereLink(Lista *lista, char *nomeOrigem, char *nomeDestino);

void retiraLink(Lista *lista, char *nomeOrigem, char *nomeDestino);

void caminho(Lista *lista, char *nomeOrigem, char *nomeDestino);

void imprimePagina(Lista *lista, char *nome);

void imprimeWided(Lista *lista);