#ifndef ListaComSentinela_h
#define ListaComSentinela_h

#include <stdio.h>

typedef struct lista Lista;

Lista* initLista(void);

// ============== Funcoes responsaveis da lista de Editores ==============
void insereEditor(Lista *lista, char *nomeEditor);

void retiraEditor(Lista *lista, char *nomeEditor);

void imprimeEditores(Lista *lista); // FUNCAO FEITA SÓ PRA AUXILIAR NO DESENVOLVIMENTO

void destroiEditores(Lista *lista);

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

#endif