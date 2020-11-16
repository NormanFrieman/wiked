#ifndef ListaComSentinela_h
#define ListaComSentinela_h

#include <stdio.h>

typedef struct lista Lista;

Lista* initLista(void);

// ============== Funcoes responsaveis da lista de Editores ==============
void insereLista(Lista *lista, char *palavra);

void retiraLista(Lista *lista, char *palavra);

void imprimeLista(Lista *lista); // FUNCAO FEITA SÓ PRA AUXILIAR NO DESENVOLVIMENTO

void destroiLista(Lista *lista);

// ============== Funcoes responsaveis da lista de Artigos ==============
void insereVoid(Lista *lista, void *item);

int retiraVoid(Lista *lista, char *nome);

void* retornaVoid(Lista *lista, char *nome);                // RETORNA UM PONTEIRO COM BASE NO NOME
void* retornaPorInt(Lista *lista, int ind);                 // RETORNA UM PONTEIRO COM BASE NA POSICAO
/*
void insereContribuicao(Lista *lista, char *nomeContribuidor, char *tituloContribuicao, char *contribuicao);

void retiraContribucao(Lista *lista, char *nome, char *nomeContribuidor, char *tituloContribuicao);

void insereLink(Lista *lista, char *nomeOrigem, char *nomeDestino);

void retiraLink(Lista *lista, char *nomeOrigem, char *nomeDestino);

void caminho(Lista *lista, char *nomeOrigem, char *nomeDestino);

void imprimePagina(Lista *lista, char *nome);

void imprimeWided(Lista *lista);
*/


// ============== Funcoes AUXILIARES ==============
void imprimeVoid(Lista *lista);

void destroiVoid(Lista *lista);

void destroiListasSecundarias(Lista *lista, int code);

#endif