#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ListaComSent.h"
//#include "GerarArtigos.h"

void INSEREPAGINA(FILE *entrada){
    char pagina[60], arquivo[60];

    fscanf(entrada, "%s", pagina);
    fscanf(entrada, "%s", arquivo);
}

void RETIRAPAGINA(FILE *entrada){
    char pagina[60];

    fscanf(entrada, "%s", pagina);
}

void INSEREEDITOR(FILE *entrada, Lista *editores){
    char editor[60];

    fscanf(entrada, "%s", editor);
    printf("INSERE EDITOR %s\n", editor);
    insereEditor(editores, editor);
    imprimeEditores(editores);
}

void RETIRAEDITOR(FILE *entrada, Lista *editores){
    char editor[60];

    fscanf(entrada, "%s", editor);
    printf("RETIRA EDITOR %s\n", editor);
    retiraEditor(editores, editor);
    imprimeEditores(editores);
}

void INSERECONTRIBUICAO(FILE *entrada){
    char pagina[60], editor[60], arquivo[60];

    fscanf(entrada, "%s", pagina);
    fscanf(entrada, "%s", editor);
    fscanf(entrada, "%s", arquivo);
}

void RETIRACONTRIBUICAO(FILE *entrada){
    char pagina[60], editor[60], arquivo[60];

    fscanf(entrada, "%s", pagina);
    fscanf(entrada, "%s", editor);
    fscanf(entrada, "%s", arquivo);
}

void INSERELINK(FILE *entrada){
    char paginaOrigem[60], paginaDestino[60];

    fscanf(entrada, "%s", paginaOrigem);
    fscanf(entrada, "%s", paginaDestino);
}

void RETIRALINK(FILE *entrada){
    char paginaOrigem[60], paginaDestino[60];

    fscanf(entrada, "%s", paginaOrigem);
    fscanf(entrada, "%s", paginaDestino);
}

void CAMINHO(FILE *entrada){
    char paginaOrigem[60], paginaDestino[60];

    fscanf(entrada, "%s", paginaOrigem);
    fscanf(entrada, "%s", paginaDestino);
}

void IMPRIMEPAGINA(FILE *entrada){
    char pagina[60];

    fscanf(entrada, "%s", pagina);
}

void IMPRIMEWIKED(){
    printf("imprimewiked\n");
}

void FIM(Lista *editores){
    destroiEditores(editores);
}

char* input(char *inp){
    char aux[60] = "entrada/";
    char *path;
    strcat(aux, inp);

    path = strdup(aux);

    return path;
}

void interpretarComando(char *url, Lista *artigos, Lista *editores){
    char linha[100];
    FILE *entrada;

    entrada = fopen(url, "r");

    if(entrada == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        while(!feof(entrada)){
            fscanf(entrada, "%s", linha);

            if(strcmp("INSEREPAGINA", linha) == 0){
                INSEREPAGINA(entrada);
            }else if(strcmp("RETIRAPAGINA", linha) == 0){
                RETIRAPAGINA(entrada);
            }else if(strcmp("INSEREEDITOR", linha) == 0){
                INSEREEDITOR(entrada, editores);
            }else if(strcmp("RETIRAEDITOR", linha) == 0){
                RETIRAEDITOR(entrada, editores);
            }else if(strcmp("INSERECONTRIBUICAO", linha) == 0){
                INSERECONTRIBUICAO(entrada);
            }else if(strcmp("RETIRACONTRIBUICAO", linha) == 0){
                RETIRACONTRIBUICAO(entrada);
            }else if(strcmp("INSERELINK", linha) == 0){
                INSERELINK(entrada);
            }else if(strcmp("RETIRALINK", linha) == 0){
                RETIRALINK(entrada);
            }else if(strcmp("CAMINHO", linha) == 0){
                CAMINHO(entrada);
            }else if(strcmp("IMPRIMEPAGINA", linha) == 0){
                IMPRIMEPAGINA(entrada);
            }else if(strcmp("IMPRIMEWIKED", linha) == 0){
                IMPRIMEWIKED();
            }else if(strcmp("FIM", linha) == 0){
                FIM(editores);
                break;
            }else{
                printf("Funcao %s nao suportada nesta versao do wikED!\n", linha);
            }
        }
    }
    fclose(entrada);
}

int main(int argc, char* argv[]){
    char *url;
    Lista *artigos, *editores;

    artigos = initLista();
    editores = initLista();

    url = input(argv[1]);

    interpretarComando(url, artigos, editores);

    free(url);
    free(artigos);

    return 0;
}