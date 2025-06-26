/**
 * Created by Clarice Curtinhas Santos on 6/6/25
 * Copyright © 2025 Clarice Curtinhas Santos, Ana Luisa Casotti de Andrade. All rights reserved.
 */

#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livro.h"
#include "leitor.h"

typedef struct Celula tCelula;

typedef struct Lista tLista;

/*
 * Cria uma nova lista, alocando memória para ela.
 * Inputs: nenhum
 * Outputs: um tipo "tLista" alocado. Primeira e última posições vazias
 * Pre-condicao: nenhuma
 * Pos-condicao: um tipo "tLista" alocado. Primeira e última posições vazias
*/
tLista *CriaLista();

/*
 * Insere um novo elemento no início da lista.
 * Inputs: ponteiro para a lista onde será inserido o elemento, ponteiro para o elemento a ser inserido
 * Outputs: nenhum
 * Pre-condicao: a lista e o elemento existem (estão alocados)
 * Pos-condicao: lista com o novo elemento inserido na primeira posição
*/
void InsereElementoLista(tLista *lista, void *elemento);

void InsereStringLista(tLista *lista, char *genero);

/*
 * Busca um leitor na lista indicada.
 * Inputs: ponteiro para a lista, leitor a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o leitor existem (estão alocados)
 * Pos-condicao: se o litor foi encontrado, retorna o ponteiro para ele, se não, retorna NULL
*/
int ProcuraCelulaLeitor(tLista *lista, tLeitor *leitor1, tLeitor *leitor2, tLista *procurados);

/*
 * Busca um leitor diferente do que já está sendo usado na lista indicada.
 * Inputs: ponteiro para a lista, leitor usado
 * Outputs: nenhum
 * Pre-condicao: a lista e o leitor existem (estão alocados)
 * Pos-condicao: se um leitor diferente for encontrado, retorna o ponteiro para ele, se não, retorna o leitor antigo
*/
tLeitor *RetornaCelulaDiferente(tLista *lista, tLista *analisadas);

/*
 * Compara as informações de duas listas de strings, para ver se existe uma info igual.
 * Inputs: ponteiro para a primrira lista e para a segunda lista que vão ser comparadas.
 * Outputs: 1 caso eles tenham informações que se repetem e 0, caso contrário.
 * Pre-condicao: as listas existem (estão alocados)
 * Pos-condicao: se a informação foi encontrado ou não, retorna os valores 1 ou 0, respectivamente
*/
int ComparaListasStrings(tLista *lista1, tLista *lista2);

/*
 * Busca um leitor na lista indicada.
 * Inputs: ponteiro para a lista, ID do leitor a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o leitor existem (estão alocados)
 * Pos-condicao: se o litor foi encontrado, retorna o ponteiro para ele, se não, retorna NULL
*/
tCelula *BuscaListaLeitor(tLista *lista, int id);

/*
 * Retorna a informação de uma celula
 * Inputs: ponteiro para uma celula
 * Outputs: a informação
 * Pre-condicao: a celula existe (está alocada)
 * Pos-condicao: a informação dentro da celula
*/
tLeitor *InfoCelulaLeitor(tCelula *cel);

/*
 * Busca um livro na lista indicada.
 * Inputs: ponteiro para a lista, ID do livro a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o livro existem (estão alocados)
 * Pos-condicao: se o livro foi encontrado, retorna o ponteiro para ele, se não, retorna NULL
*/
tCelula *BuscaListaLivro(tLista *lista, int id);

/*
 * Retorna a informação de uma celula
 * Inputs: ponteiro para uma celula
 * Outputs: a informação
 * Pre-condicao: a celula existe (está alocada)
 * Pos-condicao: a informação dentro da celula
*/
tLivro *InfoCelulaLivro(tCelula *cel);

/*
 * Compara as informações de duas listas, para ver se existe uma info igual.
 * Inputs: ponteiro para a primrira lista e para a segunda lista que vão ser comparadas.
 * Outputs: a informação, caso eles tenham informações que se repetem e NULL, caso contrário.
 * Pre-condicao: as listas existem (estão alocados)
 * Pos-condicao: se a informação foi encontrado ou não, retorna a própria info ou NULL, respectivamente
*/
tLivro *ProcuraCelulaEmComum(tLista *lista1, tLista *lista2);

/*
 * Retira um leitor da lista indicada.
 * Inputs: ponteiro para a lista, ID do leitor a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o leitor existem (estão alocados)
 * Pos-condicao: se o leitor foi encontrado, retira o leitor da lista, se não, a lista permanece inalterada
*/
void RetiraListaLeitor(tLista *lista, int id);

/*
 * Retira um livro da lista indicada.
 * Inputs: ponteiro para a lista, ID do livro a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o livro existem (estão alocados)
 * Pos-condicao: se o livro foi encontrado, retira o livro da lista, se não, a lista permanece inalterada
*/
void RetiraListaLivro(tLista *lista, int id);

/*
 * Imprime uma lista de leitores.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeListaLeitor(tLista *lista, FILE *saida);


/*
 * Imprime os nomes dos leitores.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeListaNomesLeitores(tLista *lista, FILE *saida);

/*
 * Imprime uma lista de livros.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeListaLivro(tLista *lista, FILE *saida);

/*
 * Imprime uma lista de strings.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeListaStrings(tLista *lista);

/*
 * Libera a memória de uma lista de Strings.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: memórias da lista e dos seus elementos liberadas
*/
void LiberaListaString(tLista *lista);

/*
 * Libera a memória de uma lista de celulas.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: memórias da lista e dos seus elementos liberadas
*/
void LiberaCelulas(tLista *lista);

/*
 * Libera a memória de uma lista de leitores.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: memórias da lista e dos seus elementos liberadas
*/
void LiberaListaLeitor(tLista *lista);

/*
 * Libera a memória de uma lista de livros.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: memórias da lista e dos seus elementos liberadas
*/
void LiberaListaLivro(tLista *lista);

#endif