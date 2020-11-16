#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Wiked_v1.h"

void INSEREPAGINA(FILE *entrada, Lista *artigos){
    char pagina[60], arquivo[60];

    fscanf(entrada, "%s", pagina);
    printf("INSERE PAGINA %s\n", pagina);
    fscanf(entrada, "%s", arquivo);

    inserePagina(artigos, pagina, arquivo);
}

void RETIRAPAGINA(FILE *entrada, Lista *artigos){
    char pagina[60];

    fscanf(entrada, "%s", pagina);
    printf("RETIRA PAGINA %s\n", pagina);

    retiraPagina(artigos, pagina);
}

void INSEREEDITOR(FILE *entrada, Lista *editores){
    char editor[60];

    fscanf(entrada, "%s", editor);
    printf("INSERE EDITOR %s\n", editor);
    insereEditor(editores, editor);
}

void RETIRAEDITOR(FILE *entrada, Lista *editores){
    char editor[60];

    fscanf(entrada, "%s", editor);
    printf("RETIRA EDITOR %s\n", editor);
    retiraEditor(editores, editor);
}

void INSERECONTRIBUICAO(FILE *entrada, Lista *artigos){
    char pagina[60], editor[60], arquivo[60];
    fscanf(entrada, "%s", pagina);
    fscanf(entrada, "%s", editor);
    fscanf(entrada, "%s", arquivo);

    printf("INSERE CONTRIBUICAO %s %s\n", pagina, editor);

    insereContribuicao(artigos, editor, pagina, arquivo);
}

void RETIRACONTRIBUICAO(FILE *entrada, Lista *artigos){
    char pagina[60], editor[60], arquivo[60];

    fscanf(entrada, "%s", pagina);
    fscanf(entrada, "%s", editor);
    fscanf(entrada, "%s", arquivo);

    printf("RETIRA CONTRIBUICAO %s %s\n", pagina, editor);

    retiraContribuicao(artigos, editor, pagina, arquivo);
}

void INSERELINK(FILE *entrada, Lista *artigos){
    char paginaOrigem[60], paginaDestino[60];

    fscanf(entrada, "%s", paginaOrigem);
    fscanf(entrada, "%s", paginaDestino);

    printf("INSERE LINK %s %s\n", paginaOrigem, paginaDestino);

    insereLink(artigos, paginaOrigem, paginaDestino);
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

void IMPRIMEPAGINA(FILE *entrada, Lista *artigos){
    char pagina[60];

    fscanf(entrada, "%s", pagina);

    printf("IMPRIME PAGINA %s\n", pagina);

    imprimePagina(artigos, pagina);
}

void IMPRIMEWIKED(){
    printf("imprimewiked\n");
}

void FIM(Lista *editores, Lista *artigos){
    destroiEditores(editores);
    destroiTudo(artigos);
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
        printf("Erro, nao foi possivel abrir o arquivo 'entrada.txt'\n");
    }else{
        while(!feof(entrada)){
            fscanf(entrada, "%s", linha);

            if(strcmp("INSEREPAGINA", linha) == 0){             // IMPLEMENTADO
                INSEREPAGINA(entrada, artigos);
            }else if(strcmp("RETIRAPAGINA", linha) == 0){       // IMPLEMENTADO
                RETIRAPAGINA(entrada, artigos);
            }else if(strcmp("INSEREEDITOR", linha) == 0){       // IMPLEMENTADO
                INSEREEDITOR(entrada, editores);
            }else if(strcmp("RETIRAEDITOR", linha) == 0){       // IMPLEMENTADO
                RETIRAEDITOR(entrada, editores);
            }else if(strcmp("INSERECONTRIBUICAO", linha) == 0){ // IMPLEMENTADO
                INSERECONTRIBUICAO(entrada, artigos);
            }else if(strcmp("RETIRACONTRIBUICAO", linha) == 0){ // IMPLEMENTADO
                RETIRACONTRIBUICAO(entrada, artigos);
            }else if(strcmp("INSERELINK", linha) == 0){         // IMPLEMENTADO
                INSERELINK(entrada, artigos);
            }else if(strcmp("RETIRALINK", linha) == 0){
                RETIRALINK(entrada);
            }else if(strcmp("CAMINHO", linha) == 0){
                CAMINHO(entrada);
            }else if(strcmp("IMPRIMEPAGINA", linha) == 0){
                IMPRIMEPAGINA(entrada, artigos);                // IMPLEMENTADO
            }else if(strcmp("IMPRIMEWIKED", linha) == 0){
                IMPRIMEWIKED();
            }else if(strcmp("FIM", linha) == 0){
                FIM(editores, artigos);
                break;
            }else{
                printf("Funcao %s nao suportada nesta versao do wikED!\n", linha);
            }
        }
    }
    fclose(entrada);
}

void limparTxts(){
    FILE *logs;

    logs = fopen("saida/log_test.txt", "w");

    fclose(logs);
}

int main(int argc, char* argv[]){
    char *url;
    Lista *artigos, *editores;

    limparTxts();

    artigos = initLista();
    editores = initLista();

    url = input(argv[1]);

    interpretarComando(url, artigos, editores);

    free(url);

    return 0;
}