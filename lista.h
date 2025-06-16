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

typedef int (*func_ptr_getId)(void *elemento);
typedef void (*func_ptr_imprime)(void *elemento);
typedef void (*func_ptr_libera)(void *elemento);

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
 * Busca um elemento na lista indicada.
 * Inputs: ponteiro para a lista, ID do elemento a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o elemento existem (estão alocados)
 * Pos-condicao: se o elemento foi encontrado, retorna o ponteiro para ele, se não, não retorna nada
*/
void *BuscaLista(tLista *lista, int id);

/*
 * Retira um elemento da lista indicada.
 * Inputs: ponteiro para a lista, ID do elemento a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o elemento existem (estão alocados)
 * Pos-condicao: se o elemento foi encontrado, retira o elemento da lista, se não, a lista permanece inalterada
*/
void RetiraLista(tLista *lista, int id);

/*
 * Imprime uma lista.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeLista(tLista *lista);

/*
 * Libera a memória de uma lista.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: memórias da lista e dos seus elementos liberadas
*/
void LiberaLista(tLista *lista);

#endif