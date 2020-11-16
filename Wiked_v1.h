#ifndef WikedV1_h
#define WikedV1_h

#include <stdio.h>
#include "ListaComSent.h"

typedef struct artigo Artigo;
typedef struct contrib Contribuicao;
typedef struct hist Historico;
typedef struct link Link;

Lista* iniciaLista(void);

// ============== Funcoes responsaveis da lista de Editores ==============
void insereEditor(Lista *lista, char *nomeEditor);

void retiraEditor(Lista *lista, char *nomeEditor);

void destroiEditores(Lista *lista);

// ============== Funcoes responsaveis da lista de Artigos ==============
void inserePagina(Lista *lista, char *nome, char *outfile);

void retiraPagina(Lista *lista, char *nome);

void insereContribuicao(Lista *lista, char *editor, char *pagina, char *contribuicao);

void retiraContribuicao(Lista *lista, char *editor, char *pagina, char *contribuicao);

void insereLink(Lista *lista, char *nomeOrigem, char *nomeDestino);
/*
void retiraLink(Lista *lista, char *nomeOrigem, char *nomeDestino);

void caminho(Lista *lista, char *nomeOrigem, char *nomeDestino);
*/
void imprimePagina(Lista *lista, char *pagina);

//void imprimeWided(Lista *lista);


// ============== Funcoes AUXILIARES ==============
char* retornaNome(Artigo *art);

void destroiTudo(Lista *lista);

void destroiUnitario(Artigo *art);

void destroiContrib(Contribuicao *contrib);

void destroiHist(Historico *hist);

void destroiLink(Link *link);

#endif