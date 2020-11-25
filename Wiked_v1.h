#ifndef WikedV1_h
#define WikedV1_h

#include <stdio.h>
#include "ListaComSent.h"

typedef struct artigo Artigo;

Lista* iniciaLista(void);

// ============== Funcoes responsaveis da lista de Editores ==============
void insereEditor(Lista *lista, char *nomeEditor);

void destroiEditores(Lista *lista);

// ============== Funcoes responsaveis da lista de Artigos ==============
void inserePagina(Lista *lista, char *nome, char *outfile);

void retiraPagina(Lista *lista, char *nome);

void insereContribuicao(Lista *lista, Lista *editores, char *editor, char *pagina, char *contribuicao);

void retiraContribuicao(Lista *lista, char *editor, char *pagina, char *contribuicao);

void insereLink(Lista *lista, char *nomeOrigem, char *nomeDestino);

void retiraLink(Lista *lista, char *nomeOrigem, char *nomeDestino);

void caminho(Lista *lista, char *nomeOrigem, char *nomeDestino);

void imprimePagina(Lista *lista, char *pagina);

void imprimeWiked(Lista *lista);


// ============== Funcoes AUXILIARES ==============
char* retornaNome(Artigo *art);

void destroiTudo(Lista *lista);

void destroiUnitario(Artigo *art);

#endif

/*
-Inserir uma página que já existe;
-Inserir um link que já existe;
-Inserir um editor que já existe;
-Inserir uma contribuição que já existe;
-Retirar um link que não existe;
-Retirar uma contribuição que não existe;
-Editor tentando apagar contribuição que não é dele;
-Estabelecer link entre páginas inexistentes 
*/