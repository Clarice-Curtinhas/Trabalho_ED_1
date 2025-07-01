/**
 * Created by Clarice Curtinhas Santos on 6/6/25
 * Copyright © 2025 Clarice Curtinhas Santos, Ana Luisa Casotti de Andrade. All rights reserved.
 */

#include "leitor.h"
#include "lista.h"

#define TRUE 1
#define FALSE 0

typedef struct Leitor{
    int id;
    char *nome;
    tLista *generos; //lista para guardar qual as preferências de leitura de cada leitor
    tLista *lidos;
    tLista *desejados;
    tLista *recomendacoes;
    tLista *afinidades;
} tLeitor;

/*
 * Cria um leitor novo no sistema "BookED!" a partir das informações passadas.
 * Inputs: uma string com o nome da pessoa, um int com o id da pessoa
 * Outputs: um tipo "tLeitor" alocado e com as listas criadas
 */
tLeitor *CriaLeitor(char *nome, int id){
    tLeitor *l;

    l = (tLeitor*) calloc(1, sizeof(tLeitor));

    l->nome = strdup(nome);
    l->id = id;

    l->generos = CriaLista();
    l->lidos = CriaLista();
    l->desejados = CriaLista();
    l->recomendacoes = CriaLista();
    l->afinidades = CriaLista();

    return l;
}

/*
 * Retorna o ID de um leitor.
 * Inputs: um ponteiro para um leitor
 * Outputs: o ID do leitor
 */
int GetIdLeitor(tLeitor *leitor){
    return leitor->id;
}

/*
 * Retorna o nome de um leitor.
 * Inputs: um ponteiro para um leitor
 * Outputs: o nome do leitor
 */
char *GetNomeLeitor(tLeitor *leitor){
    return leitor->nome;
}

/*
 * Adiciona um gênero literário à lista de gêneros de um leitor.
 * Inputs: um ponteiro para um leitor, uma string com o gênero
 * Outputs: nenhum
 */
void AdicionarGenero(tLeitor *leitor, char *genero){
    InsereElementoLista(leitor->generos, genero, STRING);
}

/*
 * Verifica se dois leitores leem pelo menos um gênero literário em comum. 
   Se sim, um é adicionado à lista de afinidades do outro, e vice-versa.
 * Inputs: um ponteiro para cada um dos dois leitores
 * Outputs: nenhum
 */
void AssociaLeitores(tLeitor *leitor1, tLeitor *leitor2){
    if(leitor1 != NULL && leitor2 != NULL){
        if(ComparaListasStrings(leitor1->generos, leitor2->generos) == TRUE){
            InsereElementoLista(leitor1->afinidades, leitor2, LEITOR);
            InsereElementoLista(leitor2->afinidades, leitor1, LEITOR);
        }
    }
}

/*
 * Adiciona um livro à lista de livros lidos de um leitor.
 * Inputs: um ponteiro para um leitor, um ponteiro para um livro
 * Outputs: nenhum
 */
void AdicionarLivroLido(tLeitor *leitor, tLivro *livro){
    InsereElementoLista(leitor->lidos, livro, LIVRO);
}

/*
 * Adiciona um livro à lista de livros desejados de um leitor.
 * Inputs: um ponteiro para um leitor, um ponteiro para um livro
 * Outputs: nenhum
 */
void AdicionarLivroDesejado(tLeitor *leitor, tLivro *livro){
    InsereElementoLista(leitor->desejados, livro, LIVRO);
}

/*
 * Adiciona um livro à lista de livros recomendados de um leitor se o livro ainda não estiver na lista.
 * Inputs: um ponteiro para um leitor, um ponteiro para um livro
 * Outputs: nenhum
 */
int RecebeRecomendacaoLivro(tLivro *livro, tLeitor *leitor){
    if(BuscaElementoLista(leitor->lidos, GetIdLivro(livro)) != NULL) return 1;

    else{
        InsereElementoLista(leitor->recomendacoes, livro, LIVRO);
        return 0;
    }
}

/*
 * Adiciona um livro à lista de livros desejos de um leitor se a recomendação for aceita.
   Se não, retira o livro da lista de livros recomendados.
 * Inputs: um ponteiro para um leitor, um ponteiro para um livro, um int para indicar se o a recomendação foi aceita (1) ou não (0)
 * Outputs: nenhum
 */
void AceitarRecomendacao(tLeitor *leitor, tLivro *livro, int acao){
    if(acao == TRUE){
        InsereElementoLista(leitor->desejados, livro, LIVRO);
        RetiraElementoLista(leitor->recomendacoes, GetIdLivro(livro));
    }

    else{
        RetiraElementoLista(leitor->recomendacoes, GetIdLivro(livro));
    }
}

/*
 * Compara dois leitores para ver se existe afinidade (direta ou indireta) entre eles.
 * Inputs: ponteiros para o primeiro e para o segundo leitor que vão ser comparados.
 * Outputs: 1 caso eles tenham afinidade e 0, caso contrário.
 */
int ExisteAfinidade(tLeitor *leitor1, tLeitor *leitor2){
    if (TemAfinidade(leitor1->afinidades, leitor2->afinidades) == TRUE){
        return TRUE;
    }

    else {
        tCelula *aux;
        tLeitor *leitorAux;
        aux = GetPrimeiraCelula(leitor1->afinidades);
        leitorAux = GetInfoCelula(aux);

        while(aux != NULL){
            if (TemAfinidade(leitorAux->afinidades, leitor2->afinidades) == TRUE){
                return TRUE;
            }

            else {
                aux = GetProximaCelula(aux);
                leitorAux = GetInfoCelula(aux);
            }
        }

        return FALSE;
    }
}

/*
 * Procura um livro nas listas de livro de um leitor.
 * Inputs: ponteiro para um leitor, ID do livro procurado, um int para indicar em qual das listas procurar
 * Outputs: 1 caso o livro já esteja na lista indicada e 0, caso contrário.
 */
int LivroExisteNosDadosDoLeitor(tLeitor *leitor, int id, int lista){
    tLivro *livro;

    if(lista == 1) livro = GetInfoCelula(BuscaElementoLista(leitor->lidos, id));
    else if(lista == 2) livro = GetInfoCelula(BuscaElementoLista(leitor->desejados, id));
    else if(lista == 3) livro = GetInfoCelula(BuscaElementoLista(leitor->recomendacoes, id));

    if(livro != NULL){
        return TRUE;
    }
    else return FALSE;
}

/*
 * Imprime livros em comum entre dois leitores.
 * Inputs: ponteiros para o primeiro e para o segundo leitor, ponteiro para o arquivo de saída
 * Outputs: nenhum
 */
void ImprimeLivrosEmComum(tLeitor *leitor1, tLeitor *leitor2, FILE *saida){

    ImprimeCelulasEmComum(leitor1->lidos, leitor2->lidos, saida);
}

/*
 * Imprime os dados de um leitor.
 * Inputs: ponteiro para um leitor, ponteiro para o arquivo de saída
 * Outputs: nenhum
 */
void ImprimeLeitor(tLeitor *leitor, FILE *saida){
    fprintf(saida, "Leitor: %s\n", leitor->nome);
    fprintf(saida, "Lidos: ");
    ImprimeLista(leitor->lidos, saida);
    fprintf(saida, "\nDesejados: ");
    ImprimeLista(leitor->desejados, saida);
    fprintf(saida, "\nRecomendacoes: ");
    ImprimeLista(leitor->recomendacoes, saida);
    fprintf(saida, "\nAfinidades: ");
    ImprimeListaNomesLeitores(leitor->afinidades, saida);
}

/*
 * Desaloca uma estrutura do tipo tLeitor.
 * Inputs: ponteiro para um leitor
 * Outputs: nenhum
 */
void DesalocaLeitor(tLeitor *leitor){
    if (leitor != NULL){
        LiberaCelulas(leitor->lidos);
        LiberaCelulas(leitor->desejados);
        LiberaCelulas(leitor->recomendacoes);
        LiberaLista(leitor->generos);
        LiberaCelulas(leitor->afinidades);

        free(leitor->nome);
        free(leitor);
    }
}