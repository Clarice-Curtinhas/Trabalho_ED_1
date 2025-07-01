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

#define LEITOR 1
#define LIVRO 2
#define STRING 3

typedef struct Celula tCelula;

typedef struct Lista tLista;

/*
 * Cria uma nova lista, alocando memória para ela.
 * Inputs: nenhum
 * Outputs: um tipo "tLista" alocado. Primeira e última posições vazias
 */
tLista *CriaLista();

/*
 * Insere um novo elemento no final da lista.
 * Inputs: ponteiro para a lista onde será inserido o elemento, ponteiro para o elemento a ser inserido, tipo do elemento
 * Outputs: nenhum
 */
void InsereElementoLista(tLista *lista, void *elemento, int tipo);

/*
 * Retorna a informação de uma célula
 * Inputs: ponteiro para uma célula
 * Outputs: a informação
 */
void *GetInfoCelula(tCelula *cel);

/*
 * Retorna a primeira celula da lista
 * Inputs: ponteiro para uma lista
 * Outputs: a priemira célula
 */
tCelula *GetPrimeiraCelula(tLista *lista);

/*
 * Retorna a próxima celula a partir da célula passada
 * Inputs: ponteiro para uma celula
 * Outputs: a próxima célula
 */
tCelula *GetProximaCelula(tCelula *celula);

/*
 * Busca um elemento na lista indicada.
 * Inputs: ponteiro para a lista, ID do elemento a ser procurado
 * Outputs: nenhum
 */
tCelula *BuscaElementoLista(tLista *lista, int id);

/*
 * Retira um elemento da lista indicada.
 * Inputs: ponteiro para a lista, ID do elemento a ser procurado
 * Outputs: nenhum
 */
void RetiraElementoLista(tLista *lista, int id);

/*
 * Compara as informações de duas listas de strings para ver se existe uma info igual.
 * Inputs: ponteiro para a primrira lista e para a segunda lista que vão ser comparadas.
 * Outputs: 1 caso eles tenham informações que se repetem e 0, caso contrário.
 */
int ComparaListasStrings(tLista *lista1, tLista *lista2);

/*
 * Compara duas listas de afinidade para ver se existe uma info igual.
 * Inputs: ponteiros para a primrira e para a segunda lista que vão ser comparadas.
 * Outputs: 1 caso eles tenham informações que se repetem e 0, caso contrário.
 */
int TemAfinidade(tLista *afinidades1, tLista *afinidades2);

/*
 * Imprime apenas os elementos em comum entre duas listas. Usado apenas para livros.
 * Inputs: ponteiro para a lista, arquivo de saida
 * Outputs: nenhum
 */
void ImprimeCelulasEmComum(tLista *lista1, tLista *lista2, FILE *saida);

/*
 * Imprime uma lista.
 * Inputs: ponteiro para a lista, arquivo de saida
 * Outputs: nenhum
 */
void ImprimeLista(tLista *lista, FILE *saida);

/*
 * Imprime os nomes dos leitores.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void ImprimeListaNomesLeitores(tLista *lista, FILE *saida);

/*
 * Libera a apenas a memória das celulas de uma lista.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void LiberaCelulas(tLista *lista);

/*
 * Libera a memória de uma lista (células e informações das células).
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void LiberaLista(tLista *lista);

#endif