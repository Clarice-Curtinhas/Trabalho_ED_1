/**
 * Created by Clarice Curtinhas Santos on 6/6/25
 * Copyright © 2025 Clarice Curtinhas Santos, Ana Luisa Casotti de Andrade. All rights reserved.
 */

#ifndef LEITOR_H
#define LEITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livro.h"

typedef struct Leitor tLeitor;

/*
 * Cria um leitor novo no sistema "BookED!" a partir das informações passadas.
 * Inputs: uma string com o nome da pessoa, um int com o id da pessoa
 * Outputs: um tipo "tLeitor" alocado e com as listas criadas
 */
tLeitor *CriaLeitor(char *nome, int id);

/*
 * Retorna o ID de um leitor.
 * Inputs: um ponteiro para um leitor
 * Outputs: o ID do leitor
 */
int GetIdLeitor(tLeitor *leitor);

/*
 * Retorna o nome de um leitor.
 * Inputs: um ponteiro para um leitor
 * Outputs: o nome do leitor
 */
char *GetNomeLeitor(tLeitor *leitor);

/*
 * Adiciona um gênero literário à lista de gêneros de um leitor.
 * Inputs: um ponteiro para um leitor, uma string com o gênero
 * Outputs: nenhum
 */
void AdicionarGenero(tLeitor *leitor, char *genero);

/*
 * Verifica se dois leitores leem pelo menos um gênero literário em comum. 
   Se sim, um é adicionado à lista de afinidades do outro, e vice-versa.
 * Inputs: um ponteiro para cada um dos dois leitores
 * Outputs: nenhum
 */
void AssociaLeitores(tLeitor *leitor1, tLeitor *leitor2);

/*
 * Adiciona um livro à lista de livros lidos de um leitor.
 * Inputs: um ponteiro para um leitor, um ponteiro para um livro
 * Outputs: nenhum
 */
void AdicionarLivroLido(tLeitor *leitor, tLivro *livro);

/*
 * Adiciona um livro à lista de livros desejados de um leitor.
 * Inputs: um ponteiro para um leitor, um ponteiro para um livro
 * Outputs: nenhum
 */
void AdicionarLivroDesejado(tLeitor *leitor, tLivro *livro);

/*
 * Adiciona um livro à lista de livros recomendados de um leitor se o livro ainda não estiver na lista.
 * Inputs: um ponteiro para um leitor, um ponteiro para um livro
 * Outputs: nenhum
 */
int RecebeRecomendacaoLivro(tLivro *livro, tLeitor *leitor);

/*
 * Adiciona um livro à lista de livros desejos de um leitor se a recomendação for aceita.
   Se não, retira o livro da lista de livros recomendados.
 * Inputs: um ponteiro para um leitor, um ponteiro para um livro, um int para indicar se o a recomendação foi aceita (1) ou não (0)
 * Outputs: nenhum
 */
void AceitarRecomendacao(tLeitor *leitorOrig, tLivro *livro, int acao);

/*
 * Compara dois leitores para ver se existe afinidade (direta ou indireta) entre eles.
 * Inputs: ponteiros para o primeiro e para o segundo leitor que vão ser comparados.
 * Outputs: 1 caso eles tenham afinidade e 0, caso contrário.
 */
int ExisteAfinidade(tLeitor *leitor1, tLeitor *leitor2);

/*
 * Procura um livro nas listas de livro de um leitor.
 * Inputs: ponteiro para um leitor, ID do livro procurado, um int para indicar em qual das listas procurar
 * Outputs: 1 caso o livro já esteja na lista indicada e 0, caso contrário.
 */
int LivroExisteNosDadosDoLeitor(tLeitor *leitor, int id, int lista);

/*
 * Imprime livros em comum entre dois leitores.
 * Inputs: ponteiros para o primeiro e para o segundo leitor, ponteiro para o arquivo de saída
 * Outputs: nenhum
 */
void ImprimeLivrosEmComum(tLeitor *leitor1, tLeitor *leitor2, FILE *saida);

/*
 * Imprime os dados de um leitor.
 * Inputs: ponteiro para um leitor, ponteiro para o arquivo de saída
 * Outputs: nenhum
 */
void ImprimeLeitor(tLeitor *leitor, FILE *saida);

/*
 * Desaloca uma estrutura do tipo tLeitor.
 * Inputs: ponteiro para um leitor
 * Outputs: nenhum
 */
void DesalocaLeitor(tLeitor *leitor);

#endif