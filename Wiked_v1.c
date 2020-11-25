#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Wiked_v1.h"

typedef struct contrib Contribuicao;
typedef struct hist Historico;
typedef struct link Link;

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
};

struct hist{
    char *editor;
    char *arquivo;
};

struct link{
    char *nome;
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
    char aux[60] = "saida/";
    char *path;
    strcat(aux, inp);

    path = strdup(aux);

    return path;
}

static void escreverLog(char *text, char *obj1, char *obj2){
    FILE *logs;

    logs = fopen("saida/log.txt", "a");

    if(logs == NULL){
        printf("Nao foi possivel abrir o arquivo 'log.txt'\n");
    }else{
        if(obj1 == NULL && obj2 == NULL){
            fprintf(logs, "%s\n", text);
            printf("***** %s *****\n", text);
        }else if(obj1 != NULL && obj2 == NULL){
            fprintf(logs, "%s %s\n", text, obj1);
            printf("***** %s %s *****\n", text, obj1);
        }else{
            fprintf(logs, "%s %s para %s\n", text, obj1, obj2);
            printf("***** %s %s para %s *****\n", text, obj1, obj2);
        }
    }

    fclose(logs);
}

static void imprimeEditores(Lista *lista){
    printf("EDITORES:\n");
    imprimeLista(lista);
}

static void destroiContrib(Contribuicao *contrib){
    free(contrib->nome);
    free(contrib->editor);
}

static void destroiHist(Historico *hist){
    free(hist->editor);
    free(hist->arquivo);
}

static void destroiLink(Link *link){
    free(link->nome);
    free(link->nomeArquivo);
}

static int verificaCaminho(Lista *lista, Artigo *art, char *nomeDestino, Lista *listaDeRastro){
    Link *link;
    Artigo *artAuxiliar;
    int code = 0;

    for(int i = 0; i < art->quantLinks; i++){
        link = retornaPorInt(art->links, i);
        
        char *checagem = retornaLista(listaDeRastro, link->nome);

        if(checagem == NULL){
            if(strcmp(link->nome, nomeDestino) == 0){
                return 1;
            }

            insereLista(listaDeRastro, link->nome);

            artAuxiliar = retornaVoid(lista, link->nome);
            code = verificaCaminho(lista, artAuxiliar, nomeDestino, listaDeRastro);
            
            if(code == 1){
                return 1;
            }
        }
    }

    return 0;
}
// ================================================


Lista* iniciaLista(void){
    Lista *novaLista = initLista();

    return novaLista;
}

// ============== Funcoes responsaveis da lista de Editores ==============
void insereEditor(Lista *lista, char *nomeEditor){
    char *nome = retornaLista(lista, nomeEditor);

    if(nome != NULL){
        escreverLog("ERRO: ja existe o editor", nomeEditor, NULL);
        return;
    }

    insereLista(lista, nomeEditor);
    imprimeEditores(lista);
}

void destroiEditores(Lista *lista){
    destroiLista(lista);
    free(lista);
}

// ============== Funcoes responsaveis da lista de Artigos ==============
void inserePagina(Lista *lista, char *nome, char *outfile){
    Artigo *novoArtigo = retornaVoid(lista, nome);
    if(novoArtigo != NULL){
        escreverLog("ERRO: ja existe a pagina", nome, NULL);
        return;
    }
    
    novoArtigo = (Artigo *)malloc(sizeof(Artigo));

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
    if(art == NULL){
        escreverLog("ERRO: nao existe a pagina", nome, NULL);
        return;
    }

    Link *link;

    Artigo *artAux = retornaPorInt(lista, 0);

    for(int i = 0; artAux != NULL; i++){
        if(strcmp(artAux->nome, nome) != 0){
            link = retornaPorInt(artAux->links, 0);

            if(link != NULL){                
                for(int j = 0; link != NULL; j++){
                    if(strcmp(link->nome, nome) == 0){
                        retiraLink(lista, artAux->nome, nome);
                    }
                    
                    link = retornaPorInt(artAux->links, j+1);
                }
            }
        }

        artAux = retornaPorInt(lista, i+1);
    }

    int code = retiraVoid(lista, nome);
    if(code == 0){
        escreverLog("ERRO: pagina nao removida / ERROR 500", nome, NULL);
        return;
    }

    destroiUnitario(art);
}

char* retornaNome(Artigo *art){                                          // auxiliar na remocao do artigo
    return art->nome;
}


void insereContribuicao(Lista *lista, Lista *editores, char *editor, char *pagina, char *contribuicao){
    Artigo *art = retornaVoid(lista, pagina);
    if(art == NULL){
        escreverLog("ERRO: nao existe a pagina", pagina, NULL);
        return;
    }
    char *nomeEditor = retornaLista(editores, editor);
    if(nomeEditor == NULL){
        escreverLog("ERRO: nao existe o editor", pagina, NULL);
        return;
    }
    
    Contribuicao *testContrib = retornaVoid(art->contribuicoes, contribuicao);
    if(testContrib != NULL){
        escreverLog("ERRO: ja existe na pagina a contribuicao", contribuicao, NULL);
        return;
    }

    Contribuicao *novaContrib = (Contribuicao *)malloc(sizeof(Contribuicao));
    Historico *novoHist = (Historico *)malloc(sizeof(Historico));
    
    
    novaContrib->nome = strdup(contribuicao);
    novaContrib->editor = strdup(editor);

    novoHist->editor = strdup(editor);
    novoHist->arquivo = strdup(contribuicao);
    
    insereVoid(art->historico, novoHist);
    insereVoid(art->contribuicoes, novaContrib);
    art->quantContrib++;
    art->quantEdit++;
}

void retiraContribuicao(Lista *lista, char *editor, char *pagina, char *contribuicao){
    Artigo *art = retornaVoid(lista, pagina);
    if(art == NULL){
        escreverLog("ERRO: nao existe a pagina", pagina, NULL);
        return;
    }
    
    Contribuicao *contrib = retornaVoid(art->contribuicoes, contribuicao);
    if(contrib == NULL){
        escreverLog("ERRO: nao existe a contribuicao", contribuicao, NULL);
        return;
    }

    if(strcmp(contrib->editor, editor) != 0){
        escreverLog("ERRO: editor nao tem direito de excluir esta contribuicao:", editor, NULL);
        return;
    }

    int code = retiraVoid(art->contribuicoes, contribuicao);
    
    if(code != 1){
        escreverLog("ERRO: contribuicao nao removida / ERROR 500", contribuicao, NULL);
        return;
    }

    destroiContrib(contrib);
    free(contrib);
    art->quantContrib--;
}

void insereLink(Lista *lista, char *nomeOrigem, char *nomeDestino){
    Artigo *art1 = retornaVoid(lista, nomeOrigem);
    if(art1 == NULL){
        escreverLog("ERRO: nao existe a pagina", nomeOrigem, NULL);
        return;
    }
    
    Artigo *art2 = retornaVoid(lista, nomeDestino);
    if(art2 == NULL){
        escreverLog("ERRO: nao existe a pagina", nomeDestino, NULL);
        return;
    }

    Link *test = retornaVoid(art1->links, nomeDestino);
    if(test != NULL){
        escreverLog("ERRO: ja existe um link para a pagina", nomeDestino, NULL);
    }

    Link *link = (Link *)malloc(sizeof(Link));

    link->nome = strdup(nomeDestino);
    link->nomeArquivo = strdup(art2->outfile);
    
    insereVoid(art1->links, link);
    art1->quantLinks++;
}

void retiraLink(Lista *lista, char *nomeOrigem, char *nomeDestino){
    Artigo *art1 = retornaVoid(lista, nomeOrigem);
    if(art1 == NULL){
        escreverLog("ERRO: nao existe a pagina", nomeOrigem, NULL);
        return;
    }

    Artigo *art2 = retornaVoid(lista, nomeDestino);
    if(art2 == NULL){
        escreverLog("ERRO: nao existe a pagina", nomeDestino, NULL);
        return;
    }

    Link *link = retornaVoid(art1->links, nomeDestino);

    if(link == NULL){
        escreverLog("ERRO: nao existe o link para a pagina", nomeDestino, NULL);
        return;
    }

    int code = retiraVoid(art1->links, nomeDestino);

    if(code != 1){
        escreverLog("ERRO: link nao removida / ERROR 500", nomeDestino, NULL);
        return;
    }

    destroiLink(link);
    free(link);
    art1->quantLinks--;
}

void caminho(Lista *lista, char *nomeOrigem, char *nomeDestino){
    Artigo *art1 = retornaVoid(lista, nomeOrigem);
    if(art1 == NULL){
        escreverLog("ERRO: nao existe a pagina", nomeOrigem, NULL);
        return;
    }
    
    Artigo *art2 = retornaVoid(lista, nomeDestino);
    if(art2 == NULL){
        escreverLog("ERRO: nao existe a pagina", nomeDestino, NULL);
        return;
    }

    Link *link = retornaVoid(art1->links, nomeDestino);
    
    if(link != NULL){
        escreverLog("HA CAMINHO DIRETO DA PAGINA", nomeOrigem, nomeDestino);
        return;
    }

    Lista *listaDeRastro = initLista();     // essa lista vai armazenar o nome de todos os artigos que foram verificados
    insereLista(listaDeRastro, art1->nome);

    int code = verificaCaminho(lista, art1, nomeDestino, listaDeRastro);

    destroiLista(listaDeRastro);
    free(listaDeRastro);

    if(code == 1){
        escreverLog("HA CAMINHO INDIRETO DA PAGINA", nomeOrigem, nomeDestino);
    }else{
        escreverLog("NAO HA CAMINHO DA PAGINA", nomeOrigem, nomeDestino);
    }
}

void imprimePagina(Lista *lista, char *pagina){
    Artigo *art = retornaVoid(lista, pagina);
    if(art == NULL){
        escreverLog("ERRO: nao existe a pagina", pagina, NULL);
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
        escreverLog("ERRO: criacao de um novo txt inconcluido", NULL, NULL);
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
            fprintf(saida, "%s %s\n", links->nome, links->nomeArquivo);
        }

        fprintf(saida, "\n--> Textos\n\n");
        for(int i = 0; i < art->quantContrib; i++){
            contribuicao = retornaPorInt(art->contribuicoes, i);
            fprintf(saida, "-------- %s (%s) --------\n\n", contribuicao->nome, contribuicao->editor);
            
            char *url = input(contribuicao->nome);
            entrada = fopen(url, "r");

            if(entrada == NULL){
                escreverLog("ERRO: impressao falhou da contribuicao %s", contribuicao->nome, NULL);
            }else{
                while(!feof(entrada)){
                    fscanf(entrada, "%c", &letra);
                    fprintf(saida, "%c", letra);
                }
            }

            fprintf(saida, "\n\n");

            free(url);

            fclose(entrada);
        }
    }
    fclose(saida);

    free(url);
}

void imprimeWiked(Lista *lista){
    imprimePaginas(lista);
    int i = 0;
    Artigo *art;

    for(art = retornaPorInt(lista, 0); art != NULL; i++){
        printf("%s\n", art->outfile);
        imprimePagina(lista, art->nome);
        art = retornaPorInt(lista, i+1);
    }
}




void destroiTudo(Lista *lista){
    destroiVoid(lista);
}

void destroiUnitario(Artigo *art){
    Contribuicao *contrib;
    Historico *hist;
    Link *link;
    
    contrib = retornaPorInt(art->contribuicoes, 0);
    if(contrib != NULL){
        for(int i = 0; contrib != NULL; i++){
            destroiContrib(contrib);

            contrib = retornaPorInt(art->contribuicoes, i+1);
        }

        destroiLista(art->contribuicoes);
    }

    hist = retornaPorInt(art->historico, 0);
    if(hist != NULL){
        for(int i = 0; hist != NULL; i++){
            destroiHist(hist);

            hist = retornaPorInt(art->historico, i+1);
        }

        destroiLista(art->historico);
    }

    link = retornaPorInt(art->links, 0);
    if(link != NULL){
        for(int i = 0; link != NULL; i++){
            destroiLink(link);

            link = retornaPorInt(art->links, i+1);
        }

        destroiLista(art->links);
    }

    free(art->nome);
    free(art->outfile);
    free(art->contribuicoes);
    free(art->historico);
    free(art->links);
    free(art);
}