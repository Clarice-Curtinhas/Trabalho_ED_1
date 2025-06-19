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

    LiberaListaLeitor(leitores);
    LiberaListaLivro(livros);

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
    int id, n, qntLeitores = 0;
    char nome[100], genero[100];

    while(fscanf(fp, "%d;%99[^;];%d;", &id, nome, &n) == 3){

        leitor = CriaLeitor(nome, id);

       for(int i = 0; i < n; i++){
            if(i != n-1) fscanf(fp, "%99[^;];", genero);
            else fscanf(fp, "%99[^\n]", genero);
            AdicionarGenero(leitor, genero);
        }

        InsereLeitorLista(leitores, leitor);
        qntLeitores++;
    }


    for(int i = 1; i <= qntLeitores; i++){

        for(int j = i+1; j <= qntLeitores; j++){
            AssociaLeitores(InfoCelulaLeitor(BuscaListaLeitor(leitores, i)), InfoCelulaLeitor(BuscaListaLeitor(leitores, j)));
        }
    }

    ImprimeListaLeitor(leitores);
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
        InsereLivroLista(livros, livro);
    }

    ImprimeListaLivro(livros);
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
        printf("%d; %d; %d; %d\n", func, id1, id2, id3);

        if(func == 1){
            tLeitor *leitor;
            tLivro *livro;

            leitor = InfoCelulaLeitor(BuscaListaLeitor(leitores, id1));
            livro = InfoCelulaLivro(BuscaListaLivro(livros, id2));
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            AdicionarLivroLido(leitor, livro);
        }

        else if(func == 2){
            tLeitor *leitor;
            tLivro *livro;

            leitor = InfoCelulaLeitor(BuscaListaLeitor(leitores, id1));
            livro = InfoCelulaLivro(BuscaListaLivro(livros, id2));
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            AdicionarLivroDesejado(leitor, livro);
        }

        else if(func == 3){
            tLeitor *leitorOrig, *leitorDest;

            leitorOrig = InfoCelulaLeitor(BuscaListaLeitor(leitores, id1));
            leitorDest = InfoCelulaLeitor(BuscaListaLeitor(leitores, id3));
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            //RecomendarLivro(leitorOrig, id2, leitorDest);
        }

        else if(func == 4){
            tLeitor *leitorOrig, *leitorDest;
            tLivro *livro;

            livro = InfoCelulaLivro(BuscaListaLivro(livros, id2));

            leitorOrig = InfoCelulaLeitor(BuscaListaLeitor(leitores, id1));
            leitorDest = InfoCelulaLeitor(BuscaListaLeitor(leitores, id3));
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            //AceitarRecomendacao(leitorOrig, livro, TRUE);
        }

        else if(func == 5){
            tLeitor *leitorOrig, *leitorDest;
            tLivro *livro;

            livro = InfoCelulaLivro(BuscaListaLivro(livros, id2));

            leitorOrig = InfoCelulaLeitor(BuscaListaLeitor(leitores, id1));
            leitorDest = InfoCelulaLeitor(BuscaListaLeitor(leitores, id3));
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            //AceitarRecomendacao(leitorOrig, livro, FALSE);
        }

        else if(func == 7){
            tLivro *livro;
            tLeitor *leitorOrig, *leitorDest;

            leitorOrig = InfoCelulaLeitor(BuscaListaLeitor(leitores, id1));
            leitorDest = InfoCelulaLeitor(BuscaListaLeitor(leitores, id3));
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            //livro = ProcuraLivroEmComum(leitorOrig, leitorDest);
        }

        else if(func == 7){
            int temAfinidade;
            tLeitor *leitorOrig, *leitorDest;

            leitorOrig = InfoCelulaLeitor(BuscaListaLeitor(leitores, id1));
            leitorDest = InfoCelulaLeitor(BuscaListaLeitor(leitores, id3));
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            //temAfinidade = VerificaAfinidade(leitorOrig, leitorDest);
        }

        else if(func == 8){
            ImprimeListaLeitor(leitores);
        }
    }
}