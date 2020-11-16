#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Wiked_v1.h"

struct artigo{
    char *nome;
    char *outfile;
    Lista *historico;
    Lista *contribuicoes;
    Lista *links;
    int quantContrib;
    int quantEdit;
    int quantLinks;
};

struct contrib{
    char *nome;
    char *editor;
    char *urlConteudo;
};

struct hist{
    char *editor;
    char *arquivo;
};

struct link{
    char *nomeDestino;
    char *nomeArquivo;
};

// ============== Funcoes AUXILIARES ==============
static void imprimePaginas(Lista *lista){
    printf("PAGINAS:\n");
    imprimeVoid(lista);
}

static char* input(char *inp){
    char aux[60] = "entrada/";
    char *path;
    strcat(aux, inp);

    path = strdup(aux);

    return path;
}

static char* output(char *inp){
    char aux[60] = "saida_test/";
    char *path;
    strcat(aux, inp);

    path = strdup(aux);

    return path;
}

static void escreverLog(char *text, char *obj){
    FILE *logs;

    logs = fopen("saida/log_test.txt", "a");

    if(logs == NULL){
        printf("Nao foi possivel abrir o arquivo 'log.txt'\n");
    }else{
        if(obj == NULL){
            fprintf(logs, "%s\n", text);
            printf("%s\n", text);
        }else{
            fprintf(logs, "%s %s\n", text, obj);
            printf("%s %s\n", text, obj);
        }
    }

    fclose(logs);
}

static void imprimeEditores(Lista *lista){
    printf("EDITORES:\n");
    imprimeLista(lista);
}
// ================================================


Lista* iniciaLista(void){
    Lista *novaLista = initLista();

    return novaLista;
}

// ============== Funcoes responsaveis da lista de Editores ==============
void insereEditor(Lista *lista, char *nomeEditor){
    insereLista(lista, nomeEditor);
    imprimeEditores(lista);
}

void retiraEditor(Lista *lista, char *nomeEditor){
    retiraLista(lista, nomeEditor);
    imprimeEditores(lista);
}

void destroiEditores(Lista *lista){
    destroiLista(lista);
}

// ============== Funcoes responsaveis da lista de Artigos ==============
void inserePagina(Lista *lista, char *nome, char *outfile){
    Artigo *novoArtigo = (Artigo *)malloc(sizeof(Artigo));

    novoArtigo->nome = strdup(nome);
    novoArtigo->outfile = strdup(outfile);
    novoArtigo->historico = initLista();
    novoArtigo->contribuicoes = initLista();
    novoArtigo->links = initLista();
    novoArtigo->quantContrib = 0;
    novoArtigo->quantEdit = 0;
    novoArtigo->quantLinks = 0;

    insereVoid(lista, novoArtigo);

    imprimePaginas(lista);
}


/*
    condições a serem verificadas:
        retiraVoid = 0 -->> nome não presente na lista
        retiraVoid = 1 -->> retirado
*/
void retiraPagina(Lista *lista, char *nome){
    Artigo *art = retornaVoid(lista, nome);
    int code = retiraVoid(lista, nome);

    if(code == 0){
        escreverLog("ERRO: nao existe a pagina", nome);
        return;
    }

    destroiUnitario(art);
}
char* retornaNome(Artigo *art){                                          // auxiliar na remocao do artigo
    return art->nome;
}


void insereContribuicao(Lista *lista, char *editor, char *pagina, char *contribuicao){
    Artigo *art = retornaVoid(lista, pagina);
    if(art == NULL){
        escreverLog("ERRO: nao existe a pagina", pagina);
        return;
    }
    char *url = input(contribuicao);
    
    Contribuicao *novaContrib = (Contribuicao *)malloc(sizeof(Contribuicao));
    Historico *novoHist = (Historico *)malloc(sizeof(Historico));
    
    
    novaContrib->nome = strdup(contribuicao);
    novaContrib->editor = strdup(editor);
    novaContrib->urlConteudo = strdup(url);

    novoHist->editor = strdup(editor);
    novoHist->arquivo = strdup(contribuicao);
    
    insereVoid(art->historico, novoHist);
    insereVoid(art->contribuicoes, novaContrib);
    art->quantContrib++;
    art->quantEdit++;

    free(url);
}

void retiraContribuicao(Lista *lista, char *editor, char *pagina, char *contribuicao){
    Artigo *art = retornaVoid(lista, pagina);
    if(art == NULL){
        escreverLog("ERRO: nao existe a pagina", pagina);
        return;
    }
    
    Contribuicao *contrib = retornaVoid(art->contribuicoes, contribuicao);
    if(contrib == NULL){
        escreverLog("ERRO: nao existe a contribuicao", contribuicao);
        return;
    }

    if(strcmp(contrib->editor, editor) != 0){
        escreverLog("ERRO: editor nao tem direito de excluir esta contribuicao:", editor);
        return;
    }

    int code = retiraVoid(art->contribuicoes, contribuicao);    
    
    if(code != 1){
        escreverLog("ERRO: contribuicao nao removida / ERROR 500", contribuicao);
        return;
    }

    free(contrib->nome);
    free(contrib->editor);
    free(contrib->urlConteudo);
    free(contrib);
    art->quantContrib--;
}

void insereLink(Lista *lista, char *nomeOrigem, char *nomeDestino){
    Artigo *art1 = retornaVoid(lista, nomeOrigem);
    if(art1 == NULL){
        escreverLog("ERRO: nao existe a pagina", nomeOrigem);
        return;
    }
    
    Artigo *art2 = retornaVoid(lista, nomeDestino);
    if(art2 == NULL){
        escreverLog("ERRO: nao existe a pagina", nomeDestino);
        return;
    }

    Link *link = (Link *)malloc(sizeof(Link));

    link->nomeDestino = strdup(nomeDestino);
    link->nomeArquivo = strdup(art2->outfile);
    
    insereVoid(art1->links, link);
    art1->quantLinks++;
}
/*
void retiraLink(Lista *lista, char *nomeOrigem, char *nomeDestino);

void caminho(Lista *lista, char *nomeOrigem, char *nomeDestino);
*/
void imprimePagina(Lista *lista, char *pagina){
    Artigo *art = retornaVoid(lista, pagina);
    if(art == NULL){
        escreverLog("ERRO: nao existe a pagina", pagina);
        return;
    }
    Historico *historico;
    Contribuicao *contribuicao;
    Link *links;

    FILE *saida, *entrada;
    char *url = output(art->outfile);
    char letra;

    saida = fopen(url, "w");

    if(saida == NULL){
        escreverLog("ERRO: criacao de um novo txt inconcluido", NULL);
    }else{
        fprintf(saida, "%s\n\n", art->nome);
        fprintf(saida, "--> Historico de contribuicoes\n");
        
        for(int i = 0; i < art->quantEdit; i++){
            historico = retornaPorInt(art->historico, i);
            fprintf(saida, "%s %s\n", historico->editor, historico->arquivo);
        }

        fprintf(saida, "\n--> Links\n");
        for(int i = 0; i < art->quantLinks; i++){
            links = retornaPorInt(art->links, i);
            fprintf(saida, "%s %s\n", links->nomeDestino, links->nomeArquivo);
        }

        fprintf(saida, "\n--> Textos\n\n");
        for(int i = 0; i < art->quantContrib; i++){
            contribuicao = retornaPorInt(art->contribuicoes, i);
            fprintf(saida, "-------- %s (%s) --------\n\n", contribuicao->nome, contribuicao->editor);

            entrada = fopen(contribuicao->urlConteudo, "r");

            if(entrada == NULL){
                escreverLog("ERRO: impressao falhou da contribuicao %s", contribuicao->nome);
            }else{
                while(!feof(entrada)){
                    fscanf(entrada, "%c", &letra);
                    fprintf(saida, "%c", letra);
                }
            }

            fprintf(saida, "\n\n");

            fclose(entrada);
        }
    }
    fclose(saida);

    free(url);
}

//void imprimeWided(Lista *lista);




void destroiTudo(Lista *lista){
    destroiVoid(lista);
}

void destroiContrib(Contribuicao *contrib){         // code = 0
    free(contrib->nome);
    free(contrib->editor);
    free(contrib->urlConteudo);
}

void destroiHist(Historico *hist){                  // code = 1
    free(hist->editor);
    free(hist->arquivo);
}

void destroiLink(Link *link){                       // code = 2
    free(link->nomeDestino);
    free(link->nomeArquivo);
}

void destroiUnitario(Artigo *art){
    destroiListasSecundarias(art->contribuicoes, 0);
    destroiListasSecundarias(art->historico, 1);
    destroiListasSecundarias(art->links, 2);

    free(art->nome);
    free(art->outfile);
    free(art->contribuicoes);
    free(art->historico);
    free(art->links);
    free(art);
}