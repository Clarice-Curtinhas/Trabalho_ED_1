#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitor.h"
#include "livro.h"
#include "lista.h"

#define LEITORES "test0/leitores.txt"
#define LIVROS "test0/livros.txt"
#define COMANDOS "test0/comandos.txt"
#define SAIDA "saida0.txt"

#define TRUE 1
#define FALSE 0

#define ORIGINAL -1
#define DESTINATARIO -2

char *RetiraEspacosString(char *string);

/*
 * Inicializa a lista de leitores, fazendo as associações de afinidades.
 * Inputs: um tipo "tLista" onde serão alocados os leitores e um FILE *fp para a leitura dos dados
 * Outputs: nenhuma
 */
void LerLeitores(tLista *leitores, FILE *fp);

/*
 * Inicializa a lista de livros.
 * Inputs: um tipo "tLista" onde serão alocados os livros e um FILE *fp para a leitura dos dados
 * Outputs: nenhuma
 */
void LerLivros(tLista *livros, FILE *fp);

/*
 * Execução dos comandos existentes em 'comandos.txt'
 * Inputs: dois tipos "tLista" onde estarão as informações sobre os leitores e os livros e um FILE *fp para a leitura dos dados
 * Outputs: nenhuma
 */
void ExecutarComandos(tLista *leitores, tLista *livros, FILE *fp, FILE *saida);

/*
 * Inicializa e executa o programa com os arquivos de inicialização
 * Inputs: argc e argv para ter acesso aos documentos de inicialização
 * Outputs: um tipo "tLista" alocado. Primeira e última posições vazias
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

    LiberaLista(livros);
    LiberaLista(leitores);

    return 0;
}

char *RetiraEspacosString(char *string){
    int tam;

    tam = strlen(string);

    if(string[0] == ' '){
        for(int i = 0; i < tam; i++){
            if(i+1 != tam) string[i] = string[i+1];
            else string[i] = '\0';
        }
    }

    tam = strlen(string);

    if(string[tam-1] == ' '){
        string[tam-1] = '\0';
    }

    return string;
}

/*
 * Inicializa a lista de leitores, fazendo as associações de afinidades.
 * Inputs: um tipo "tLista" onde serão alocados os leitores e um FILE *fp para a leitura dos dados
 * Outputs: nenhuma
 */
void LerLeitores(tLista *leitores, FILE *fp){
    tLeitor *leitor;
    int id, n, qntLeitores = 0;
    char nome[100], genero[100], verifica[100];

    fscanf(fp, "%99[^\n]", verifica);

    while(fscanf(fp, "%d;%99[^;];%d;", &id, nome, &n) == 3){

        leitor = CriaLeitor(nome, id);

        printf("%s\n", nome);

       for(int i = 0; i < n; i++){
            if(i != n-1) fscanf(fp, "%99[^;];", genero);
            else fscanf(fp, "%99[^\n]", genero);
            AdicionarGenero(leitor, RetiraEspacosString(genero));
        }

        InsereElementoLista(leitores, leitor, LEITOR);
        qntLeitores++;
    }


    for(int i = 1; i <= qntLeitores; i++){
        for(int j = i+1; j <= qntLeitores; j++){
            AssociaLeitores(GetInfoCelula(BuscaElementoLista(leitores, i)), GetInfoCelula(BuscaElementoLista(leitores, j)));
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
        InsereElementoLista(livros, livro, LIVRO);
    }
}

tLeitor *EncontraLeitor(tLista *leitores, int id, FILE *saida, int comando, int tipoLeitor){
    if(BuscaElementoLista(leitores, id) != NULL){
        return GetInfoCelula(BuscaElementoLista(leitores, id));
    }

    else{
        if (comando == 3){
            if (tipoLeitor == ORIGINAL) fprintf(saida, "Erro: Leitor recomendador com ID %d não encontrado\n", id);
            else if (tipoLeitor == DESTINATARIO) fprintf(saida, "Erro: Leitor destinatário com ID %d não encontrado\n", id);
        }

        else if (comando == 4 || comando == 5){
            if (tipoLeitor == ORIGINAL) fprintf(saida, "Erro: Leitor recomendador com ID %d não encontrado\n", id);
            else if (tipoLeitor == DESTINATARIO) fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", id);
        }

        /*else if (comando == 5){
            if (tipoLeitor == DESTINATARIO) fprintf(saida, "Erro: Leitor recomendador com ID %d não encontrado\n", id);
            else if (tipoLeitor == ORIGINAL) fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", id);
        }*/

        else if (comando == 1 || comando == 2 || comando == 6 || comando == 7){
            fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", id);
        }
        return NULL;
    }
}

tLivro *EncontraLivro(tLista *livros, int id, FILE *saida, int comando){
    if(BuscaElementoLista(livros, id) != NULL){
        return GetInfoCelula(BuscaElementoLista(livros, id));
    }

    else{
        if (comando != 4 && comando != 5) fprintf(saida, "Erro: Livro com ID %d não encontrado\n", id);
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

        printf("funcao %d\n", func);

        if(func == 1){
            tLeitor *leitor;
            tLivro *livro;

            leitor = EncontraLeitor(leitores, id1, saida, 1, 0);
            livro = EncontraLivro(livros, id2, saida, 1);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)
            if(leitor != NULL && livro != NULL){
                if (LivroExisteNosDadosDoLeitor(leitor, id2, 1) == TRUE){
                    fprintf(saida, "%s já leu \"%s\"\n", GetNomeLeitor(leitor), GetNomeLivro(livro));
                }

                else {
                    AdicionarLivroLido(leitor, livro);
                    fprintf(saida, "%s leu \"%s\"\n", GetNomeLeitor(leitor), GetNomeLivro(livro));
                }
            }

            printf("comando 1\n");
        }

        else if(func == 2){
            tLeitor *leitor;
            tLivro *livro;

            leitor = EncontraLeitor(leitores, id1, saida, 2, 0);
            livro = EncontraLivro(livros, id2, saida, 2);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            if(leitor != NULL && livro != NULL){
                if (LivroExisteNosDadosDoLeitor(leitor, id2, 2) == TRUE){
                    fprintf(saida, "%s já deseja ler \"%s\"\n", GetNomeLeitor(leitor), GetNomeLivro(livro));
                }
                
                else {
                    AdicionarLivroDesejado(leitor, livro);
                    fprintf(saida, "%s deseja ler \"%s\"\n", GetNomeLeitor(leitor), GetNomeLivro(livro));
                }
            }

            printf("comando 2\n");
        }

        else if(func == 3){
            tLeitor *leitorOrig, *leitorDest;
            tLivro *livro;
            int jaLeu = 0;

            leitorOrig = EncontraLeitor(leitores, id1, saida, 3, ORIGINAL);
            leitorDest = EncontraLeitor(leitores, id3, saida, 3, DESTINATARIO);
            livro = EncontraLivro(livros, id2, saida, 3);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            if(leitorOrig != NULL && leitorDest != NULL && livro != NULL){
                jaLeu = RecebeRecomendacaoLivro(livro, leitorDest);

                if (id1 == id3) {
                    fprintf(saida, "%s não pode recomendar livros para si mesmo\n", GetNomeLeitor(leitorOrig));
                    AceitarRecomendacao(leitorDest, livro, FALSE);
                }

                else if(jaLeu == 0) {
                    if (LivroExisteNosDadosDoLeitor(leitorDest, id2, 2) == TRUE){
                        fprintf(saida, "%s já deseja ler \"%s\", recomendação desnecessária\n", GetNomeLeitor(leitorDest), GetNomeLivro(livro));
                        AceitarRecomendacao(leitorDest, livro, FALSE);
                    }

                    else {
                        fprintf(saida, "%s recomenda \"%s\" para %s\n", GetNomeLeitor(leitorOrig), GetNomeLivro(livro), GetNomeLeitor(leitorDest));
                    }
                }
                else {
                    fprintf(saida, "%s não precisa da recomendação de \"%s\" pois já leu este livro\n", GetNomeLeitor(leitorDest), GetNomeLivro(livro));
                    AceitarRecomendacao(leitorDest, livro, FALSE);
                }
            }

            printf("comando 3\n");
        }

        else if(func == 4){
            tLeitor *leitorOrig, *leitorDest;
            tLivro *livro;

            leitorOrig = EncontraLeitor(leitores, id1, saida, 4, DESTINATARIO);
            leitorDest = EncontraLeitor(leitores, id3, saida, 4, ORIGINAL);
            if (leitorOrig == NULL || leitorDest == NULL) continue;

            livro = EncontraLivro(livros, id2, saida, 4);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            if(leitorOrig != NULL && leitorDest != NULL){
                if(LivroExisteNosDadosDoLeitor(leitorOrig, id2, 3) == TRUE){
                    AceitarRecomendacao(leitorOrig, livro, TRUE);
                    fprintf(saida, "%s aceita recomendação \"%s\" de %s\n", GetNomeLeitor(leitorOrig), GetNomeLivro(livro), GetNomeLeitor(leitorDest));
                }

                else{
                    fprintf(saida, "%s não possui recomendação do livro ID %d feita por %s\n", GetNomeLeitor(leitorOrig), id2, GetNomeLeitor(leitorDest));
                }
            }
            printf("comando 4\n");
        }

        else if(func == 5){
            tLeitor *leitorOrig, *leitorDest;
            tLivro *livro;

            livro = EncontraLivro(livros, id2, saida, 5);

            leitorOrig = EncontraLeitor(leitores, id1, saida, 5, DESTINATARIO);
            leitorDest = EncontraLeitor(leitores, id3, saida, 5, ORIGINAL);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            if(leitorOrig != NULL && leitorDest != NULL){
                if(LivroExisteNosDadosDoLeitor(leitorOrig, id2, 3) == TRUE){
                    AceitarRecomendacao(leitorOrig, livro, FALSE);
                    fprintf(saida, "%s rejeita recomendação \"%s\" de %s\n", GetNomeLeitor(leitorOrig), GetNomeLivro(livro), GetNomeLeitor(leitorDest));
                }

                else{
                    fprintf(saida, "%s não possui recomendação do livro ID %d feita por %s\n", GetNomeLeitor(leitorOrig), id2, GetNomeLeitor(leitorDest));
                }
            }
            printf("comando 5\n");
        }

        else if(func == 6){
            tLista *livrosEmComum = CriaLista();
            tLeitor *leitorOrig, *leitorDest;
            int qtdEmComum;

            leitorOrig = EncontraLeitor(leitores, id1, saida, 6, ORIGINAL);
            leitorDest = EncontraLeitor(leitores, id3, saida, 6, DESTINATARIO);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            if(leitorOrig != NULL && leitorDest != NULL){
                fprintf(saida, "Livros em comum entre %s e %s: ", GetNomeLeitor(leitorOrig), GetNomeLeitor(leitorDest));


                ImprimeLivrosEmComum(leitorOrig, leitorDest, saida);
                
            }

            printf("comando 6\n");
        }

        else if(func == 7){
            int temAfinidade;
            tLeitor *leitorOrig, *leitorDest;

            leitorOrig = EncontraLeitor(leitores, id1, saida, 7, ORIGINAL);
            leitorDest = EncontraLeitor(leitores, id3, saida, 7, DESTINATARIO);
            //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
            //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

            if(leitorOrig != NULL && leitorDest != NULL){
                //fprintf(saida, "\nFuncao 7: ##Estava dando errado, por isso comentei##\n\n");
                temAfinidade = ExisteAfinidade(leitorOrig, leitorDest);

                if(temAfinidade == TRUE) fprintf(saida, "Existe afinidade entre %s e %s\n", GetNomeLeitor(leitorOrig), GetNomeLeitor(leitorDest));
                else fprintf(saida, "Não existe afinidade entre %s e %s\n", GetNomeLeitor(leitorOrig), GetNomeLeitor(leitorDest));
            }
            printf("comando 7\n");
        }

        else if(func == 8){
            fprintf(saida, "Imprime toda a BookED\n\n");
            ImprimeLista(leitores, saida);
            printf("comando 8\n");
        }

        else fprintf(saida, "Erro: Comando %d não reconhecido\n", func);
    }
}