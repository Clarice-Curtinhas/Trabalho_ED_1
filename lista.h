/**
 * Created by Clarice Curtinhas Santos on 6/6/25
 * Copyright © 2025 Clarice Curtinhas Santos, Ana Luisa Casotti de Andrade. All rights reserved.
 */

#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void InsereLista(tLista *lista, void *elemento);

/*
 * Busca um leitor na lista indicada.
 * Inputs: ponteiro para a lista, ID do leitor a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o leitor existem (estão alocados)
 * Pos-condicao: se o litor foi encontrado, retorna o ponteiro para ele, se não, retorna NULL
*/
void *BuscaListaLeitor(tLista *lista, int id);

/*
 * Busca um livro na lista indicada.
 * Inputs: ponteiro para a lista, ID do livro a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o livro existem (estão alocados)
 * Pos-condicao: se o livro foi encontrado, retorna o ponteiro para ele, se não, retorna NULL
*/
void *BuscaListaLivro(tLista *lista, int id);

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
void ImprimeListaLeitor(tLista *lista);

/*
 * Imprime uma lista de livros.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeListaLivro(tLista *lista);

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