#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitor.h"
#include "livro.h"
#include "lista.h"

#define TRUE 1
#define FALSE 0

/*
 * Inicializa a lista de leitores, fazendo as associações de afinidades.
 * Inputs: um tipo "tLista" onde serão alocados os leitores e um FILE *fp para a leitura dos dados
 * Outputs: nenhuma
 * Pre-condicao: um tipo "tLista" vazio e um FILE *fp com os dados de leitores
 * Pos-condicao: nenhum
*/
void LerLeitores(tLista *leitores, FILE *fp);

/*
 * Inicializa a lista de livros.
 * Inputs: um tipo "tLista" onde serão alocados os livros e um FILE *fp para a leitura dos dados
 * Outputs: nenhuma
 * Pre-condicao: um tipo "tLista" vazio e um FILE *fp com os dados de livros
 * Pos-condicao: nenhum
*/
void LerLivros(tLista *livros, FILE *fp);

/*
 * Execução dos comandos existentes em 'comandos.txt'
 * Inputs: dois tipos "tLista" onde estarão as informações sobre os leitores e os livros e um FILE *fp para a leitura dos dados
 * Outputs: nenhuma
 * Pre-condicao: um FILE *fp com os comandos ordenados
 * Pos-condicao: nenhum
*/
void ExecutarComandos(tLista *leitores, tLista *livros, FILE *fp);

/*
 * Inicializa e executa o programa com os arquivos de inicialização
 * Inputs: argc e argv para ter acesso aos documentos de inicialização
 * Outputs: um tipo "tLista" alocado. Primeira e última posições vazias
 * Pre-condicao: nenhuma
 * Pos-condicao: nenhuma
*/
int main(int argc, const char **argv){
    tLista *leitores, *livros;

    leitores = CriaLista();
    livros = CriaLista();

    if(argc < 2) {
        printf("Uso: %s <diretorio>\n", argv[0]);
        return 1;
    }    

    FILE *fp;
    char diretorio[100];

    strcpy(diretorio, argv[1]);
    strcat(diretorio, "/leitores.txt");

    fp = fopen(diretorio, "r");

    if(fp == NULL){
        printf("ERRO: nao foi possivel abrir o arquivo 'leitores.txt'.\n");
        exit(1);
    }

    else LerLeitores(leitores, fp);

    fclose(fp);

    strcpy(diretorio, argv[1]);
    strcat(diretorio, "/livro.txt");

    fp = fopen(diretorio, "r");

    if(fp == NULL){
        printf("ERRO: nao foi possivel abrir o arquivo 'livro.txt'.\n");
        exit(1);
    }

    else LerLivros(livros, fp);

    fclose(fp);

    strcpy(diretorio, argv[1]);
    strcat(diretorio, "/comandos.txt");

    fp = fopen(diretorio, "r");

    if(fp == NULL){
        printf("ERRO: nao foi possivel abrir o arquivo 'comandos.txt'.\n");
        exit(1);
    }

    else ExecutarComandos(leitores, livros, fp);

    fclose(fp);

    LiberaLista(leitores);
    LiberaLista(livros);

    return 0;
}

/*
 * Inicializa a lista de leitores, fazendo as associações de afinidades.
 * Inputs: um tipo "tLista" onde serão alocados os leitores e um FILE *fp para a leitura dos dados
 * Outputs: nenhuma
 * Pre-condicao: um tipo "tLista" vazio e um FILE *fp com os dados de leitores
 * Pos-condicao: nenhum
*/
void LerLeitores(tLista *leitores, FILE *fp){
    tLeitor *leitor;
    int id, n;
    char nome[100], afinidade[100];

    while(fscanf(fp, "%d;%99[^;];%d", &id, nome, &n) == 3){

        leitor = CriaLeitor(nome, id);

        for(int i = 0; i < n; i++){
            fscanf(fp, "%99[^\n]", afinidade);
            //AdicionarAfinidade(leitor, afinidade);
        }

        InsereLista(leitores, leitor);
    }
}

/*
 * Inicializa a lista de livros.
 * Inputs: um tipo "tLista" onde serão alocados os livros e um FILE *fp para a leitura dos dados
 * Outputs: nenhuma
 * Pre-condicao: um tipo "tLista" vazio e um FILE *fp com os dados de livros
 * Pos-condicao: nenhum
*/
void LerLivros(tLista *livros, FILE *fp){
    tLivro *livro;
    int id, ano;
    char titulo[100], autor[100], genero[100];

    while(fscanf(fp, "%d;%99[^;];%99[^;];%99[^;];%d", &id, titulo, autor, genero, &ano) == 5){

        livro = CadastraLivro(id, titulo, autor, genero, ano);

        InsereLista(livros, livro);
    }
}

/*
 * Execução dos comandos existentes em 'comandos.txt'
 * Inputs: dois tipos "tLista" onde estarão as informações sobre os leitores e os livros e um FILE *fp para a leitura dos dados
 * Outputs: nenhuma
 * Pre-condicao: um FILE *fp com os comandos ordenados
 * Pos-condicao: nenhum
*/
void ExecutarComandos(tLista *leitores, tLista *livros, FILE *fp){
    int func, id1, id2, id3;

    while(fscanf(fp, "%d;%d;%d;%d", &func, &id1, &id2, &id3) == 4){
        return;
    }
}