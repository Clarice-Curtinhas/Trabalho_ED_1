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
 * Insere um novo elemento no início da lista.
 * Inputs: ponteiro para a lista onde será inserido o elemento, ponteiro para o elemento a ser inserido
 * Outputs: nenhum
 */
void InsereElementoLista(tLista *lista, void *elemento);

void InsereStringLista(tLista *lista, char *genero);

void DefineTipoLeitor(tLista *lista);

void DefineTipoLivro(tLista *lista);

/*
 * Busca um leitor na lista indicada.
 * Inputs: ponteiro para a lista, leitor a ser procurado
 * Outputs: nenhum
 */
int ProcuraCelulaLeitor(tLista *lista, tLeitor *leitor);

tCelula *GetPrimeiraCelula(tLista *lista);

tCelula *GetProximaCelula(tCelula *celula);
/*
 * Busca um leitor diferente do que já está sendo usado na lista indicada.
 * Inputs: ponteiro para a lista, leitor usado
 * Outputs: nenhum
 */
tLeitor *RetornaCelulaDiferente(tLista *lista, tLista *analisadas);

/*
 * Compara as informações de duas listas de strings, para ver se existe uma info igual.
 * Inputs: ponteiro para a primrira lista e para a segunda lista que vão ser comparadas.
 * Outputs: 1 caso eles tenham informações que se repetem e 0, caso contrário.
 */
int ComparaListasStrings(tLista *lista1, tLista *lista2);

/*
 * Busca um elemento na lista indicada.
 * Inputs: ponteiro para a lista, ID do elemento a ser procurado
 * Outputs: nenhum
 */
tCelula *BuscaElementoLista(tLista *lista, int id);

/*
 * Retorna a informação de uma celula
 * Inputs: ponteiro para uma celula
 * Outputs: a informação
 */
tLeitor *InfoCelulaLeitor(tCelula *cel);

/*
 * Retorna a informação de uma celula
 * Inputs: ponteiro para uma celula
 * Outputs: a informação
 */
tLivro *InfoCelulaLivro(tCelula *cel);

/*
 * Compara as informações de duas listas, para ver se existe uma info igual.
 * Inputs: ponteiro para a primrira lista e para a segunda lista que vão ser comparadas.
 * Outputs: a informação, caso eles tenham informações que se repetem e NULL, caso contrário.
 */
int ProcuraCelulasEmComum(tLista *lista1, tLista *lista2, tLista *livrosEmComum);

/*
 * Retira um elemento da lista indicada.
 * Inputs: ponteiro para a lista, ID do elemento a ser procurado
 * Outputs: nenhum
 */
void RetiraElementoLista(tLista *lista, int id);

void ImprimeCelulasEmComum(tLista *lista1, tLista *lista2, FILE *saida);

/*
 * Imprime uma lista de leitores.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void ImprimeListaLeitor(tLista *lista, FILE *saida);


/*
 * Imprime os nomes dos leitores.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void ImprimeListaNomesLeitores(tLista *lista, FILE *saida);

/*
 * Imprime uma lista de livros.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void ImprimeListaLivro(tLista *lista, FILE *saida);

/*
 * Imprime uma lista de strings.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void ImprimeListaStrings(tLista *lista);

/*
 * Libera a memória de uma lista de Strings.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void LiberaListaString(tLista *lista);

/*
 * Libera a memória de uma lista de celulas.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void LiberaCelulas(tLista *lista);

/*
 * Libera a memória de uma lista.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void LiberaLista(tLista *lista);

#endif