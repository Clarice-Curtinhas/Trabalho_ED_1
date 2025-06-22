#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitor.h"
#include "livro.h"
#include "lista.h"

#define LEITORES "test3/leitores.txt"
#define LIVROS "test3/livros.txt"
#define COMANDOS "test3/comandos.txt"
#define SAIDA "saida3.txt"

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
void ExecutarComandos(tLista *leitores, tLista *livros, FILE *fp, FILE *saida);

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

    FILE *fp, *saida;
    char diretorio[100];

    strcpy(diretorio, argv[1]);
    strcat(diretorio, LEITORES);

    fp = fopen(diretorio, "r");

    if(fp == NULL){
        printf("ERRO: nao foi possivel abrir o arquivo 'leitores.txt'.\n");
        exit(1);
    }

    else LerLeitores(leitores, fp);

    fclose(fp);

    strcpy(diretorio, argv[1]);
    strcat(diretorio, LIVROS);

    fp = fopen(diretorio, "r");

    if(fp == NULL){
        printf("ERRO: nao foi possivel abrir o arquivo 'livros.txt'.\n");
        exit(1);
    }

    else LerLivros(livros, fp);

    fclose(fp);

    strcpy(diretorio, argv[1]);
    strcat(diretorio, COMANDOS);

    fp = fopen(diretorio, "r");

    strcpy(diretorio, argv[1]);
    strcat(diretorio, SAIDA);

    saida = fopen(diretorio, "w");

    if(fp == NULL){
        printf("ERRO: nao foi possivel abrir o arquivo 'comandos.txt'.\n");
        exit(1);
    }

    else if(saida == NULL){
        printf("ERRO: nao foi possivel abrir o arquivo 'saida.txt'.\n");
        exit(1);
    }

    else ExecutarComandos(leitores, livros, fp, saida);

    fclose(saida);
    fclose(fp);

    LiberaListaLivro(livros);
    LiberaListaLeitor(leitores);

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
    char nome[100], genero[100], verifica[100];

    fscanf(fp, "%99[^\n]", verifica);

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
    char titulo[100], autor[100], genero[100], verifica[100];

    fscanf(fp, "%99[^\n]", verifica);

    while(fscanf(fp, "%d;%99[^;];%99[^;];%99[^;];%d", &id, titulo, autor, genero, &ano) == 5){

        //printf("%d; %s; %s; %s; %d", id, titulo, autor, genero, ano);
        livro = CadastraLivro(id, titulo, autor, genero, ano);
        InsereLivroLista(livros, livro);
    }
}

tLeitor *EncontraLeitor(tLista *leitores, int id, FILE *saida){
    if(BuscaListaLeitor(leitores, id) != NULL){
        return InfoCelulaLeitor(BuscaListaLeitor(leitores, id));
    }

    else{
        fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", id);
        return NULL;
    }
}

tLivro *EncontraLivro(tLista *livros, int id, FILE *saida){
    if(BuscaListaLivro(livros, id) != NULL){
        return InfoCelulaLivro(BuscaListaLivro(livros, id));
    }

    else{
        fprintf(saida, "Erro: Livro com ID %d não encontrado\n", id);
        return NULL;
    }
}

/*
 * Execução dos comandos existentes em 'comandos.txt'
 * Inputs: dois tipos "tLista" onde estarão as informações sobre os leitores e os livros e um FILE *fp para a leitura dos dados
 * Outputs: nenhuma
 * Pre-condicao: um FILE *fp com os comandos ordenados
 * Pos-condicao: nenhum
*/
void ExecutarComandos(tLista *leitores, tLista *livros, FILE *fp, FILE *saida){
    int func, id1, id2, id3;
    char verifica[100];

    fscanf(fp, "%99[^\n]", verifica);

    while(fscanf(fp, "%d;%d;%d;%d", &func, &id1, &id2, &id3) == 4){

        if(func == 1){
            tLeitor *leitor;
            tLivro *livro;

            leitor = EncontraLeitor(leitores, id1, saida);
            livro = EncontraLivro(livros, id2, saida);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)
            if(leitor != NULL && livro != NULL){
                AdicionarLivroLido(leitor, livro);
                fprintf(saida, "%s leu \"%s\"\n", GetNomeLeitor(leitor), GetNomeLivro(livro));
            }
        }

        else if(func == 2){
            tLeitor *leitor;
            tLivro *livro;

            leitor = EncontraLeitor(leitores, id1, saida);
            livro = EncontraLivro(livros, id2, saida);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            if(leitor != NULL && livro != NULL){
                AdicionarLivroDesejado(leitor, livro);
                fprintf(saida, "%s deseja ler \"%s\"\n", GetNomeLeitor(leitor), GetNomeLivro(livro));
            }
        }

        else if(func == 3){
            tLeitor *leitorOrig, *leitorDest;
            tLivro *livro;
            int jaLeu = 0;

            leitorOrig = EncontraLeitor(leitores, id1, saida);
            leitorDest = EncontraLeitor(leitores, id3, saida);
            livro = EncontraLivro(livros, id2, saida);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            if(leitorOrig != NULL && leitorDest != NULL && livro != NULL){
                jaLeu = RecebeRecomendacaoLivro(livro, leitorDest);

                if(jaLeu == 0) fprintf(saida, "%s recomenda \"%s\" para %s\n", GetNomeLeitor(leitorOrig), GetNomeLivro(livro), GetNomeLeitor(leitorDest));

                else fprintf(saida, "%s não precisa da recomendação de \"%s\" pois já leu este livro\n", GetNomeLeitor(leitorDest), GetNomeLivro(livro));
            }
        }

        else if(func == 4){
            tLeitor *leitorOrig, *leitorDest;
            tLivro *livro;

            livro = EncontraLivro(livros, id2, saida);

            leitorOrig = EncontraLeitor(leitores, id1, saida);
            leitorDest = EncontraLeitor(leitores, id3, saida);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            if(leitorOrig != NULL && leitorDest != NULL && livro != NULL){
                if(LivroExisteNosDadosDoLeitor(leitorOrig, id2, 3) == TRUE){
                    AceitarRecomendacao(leitorOrig, livro, TRUE);
                    fprintf(saida, "%s aceita recomendação \"%s\" de %s\n", GetNomeLeitor(leitorOrig), GetNomeLivro(livro), GetNomeLeitor(leitorDest));
                }

                else{
                    fprintf(saida, "%s não possui recomendação do livro ID %d feito por %s\n", GetNomeLeitor(leitorOrig), id2, GetNomeLeitor(leitorDest));
                }
            }
        }

        else if(func == 5){
            tLeitor *leitorOrig, *leitorDest;
            tLivro *livro;

            livro = EncontraLivro(livros, id2, saida);

            leitorOrig = EncontraLeitor(leitores, id1, saida);
            leitorDest = EncontraLeitor(leitores, id3, saida);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            if(leitorOrig != NULL && leitorDest != NULL && livro != NULL){
                if(LivroExisteNosDadosDoLeitor(leitorOrig, id2, 3) == 1){
                    AceitarRecomendacao(leitorOrig, livro, FALSE);
                    fprintf(saida, "%s rejeita recomendação \"%s\" de %s\n", GetNomeLeitor(leitorOrig), GetNomeLivro(livro), GetNomeLeitor(leitorDest));
                }

                else{
                    fprintf(saida, "%s não possui recomendação do livro ID %d feito por %s\n", GetNomeLeitor(leitorOrig), id2, GetNomeLeitor(leitorDest));
                }
            }
        }

        else if(func == 6){
            tLivro *livro;
            tLeitor *leitorOrig, *leitorDest;

            leitorOrig = EncontraLeitor(leitores, id1, saida);
            leitorDest = EncontraLeitor(leitores, id3, saida);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            if(leitorOrig != NULL && leitorDest != NULL){
                livro = ProcuraLivroEmComum(leitorOrig, leitorDest);

                if(livro != NULL) fprintf(saida, "Livros em comum entre %s e %s: %s\n", GetNomeLeitor(leitorOrig), GetNomeLeitor(leitorDest), GetNomeLivro(livro));
                else fprintf(saida, "Livros em comum entre %s e %s: Nenhum livro em comum\n", GetNomeLeitor(leitorOrig), GetNomeLeitor(leitorDest));
            }
        }

        else if(func == 7){
            int temAfinidade;
            tLeitor *leitorOrig, *leitorDest;

            leitorOrig = EncontraLeitor(leitores, id1, saida);
            leitorDest = EncontraLeitor(leitores, id3, saida);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            if(leitorOrig != NULL && leitorDest != NULL){
                //fprintf(saida, "\nFuncao 7: ##Estava dando errado, por isso comentei##\n\n");
                temAfinidade = VerificaAfinidade(leitorOrig, leitorDest);

                if(temAfinidade == TRUE) fprintf(saida, "Existe afinidade entre %s e %s\n", GetNomeLeitor(leitorOrig), GetNomeLeitor(leitorDest));
                else fprintf(saida, "Não existe afinidade entre %s e %s\n", GetNomeLeitor(leitorOrig), GetNomeLeitor(leitorDest));
            }
        }

        else if(func == 8){
            fprintf(saida, "Imprime toda a BookED\n\n");
            ImprimeListaLeitor(leitores, saida);
        }

        else fprintf(saida, "Erro: Comando %d não reconhecido\n", func);
    }
}