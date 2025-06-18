/**
 * Created by Clarice Curtinhas Santos on 6/6/25
 * Copyright © 2025 Clarice Curtinhas Santos, Ana Luisa Casotti de Andrade. All rights reserved.
 */

#include "lista.h"

struct Celula {
   int tipo;
   void *info;
   tCelula *prox;
   tCelula *ant;
};

struct Lista {
   tCelula *prim;
   tCelula *ult;
};

/*
 * Cria uma nova lista, alocando memória para ela.
 * Inputs: nenhum
 * Outputs: um tipo "tLista" alocado. Primeira e última posições vazias
 * Pre-condicao: nenhuma
 * Pos-condicao: um tipo "tLista" alocado. Primeira e última posições vazias
*/
tLista *CriaLista(){
   tLista *lista = (tLista*) calloc(1, sizeof(tLista));

   lista->prim = NULL;
   lista->ult = NULL;

   return lista;
}

/*
 * Insere um novo elemento no início da lista.
 * Inputs: ponteiro para a lista onde será inserido o elemento, ponteiro para o elemento a ser inserido
 * Outputs: nenhum
 * Pre-condicao: a lista e o elemento existem (estão alocados)
 * Pos-condicao: lista com o novo elemento inserido na primeira posição
*/
void InsereLista(tLista *lista, void *elemento){
   tCelula *nova = (tCelula*) calloc(1, sizeof(tCelula));

   if (elemento != NULL){
      nova->info = elemento;
      nova->prox = lista->prim;

      if (lista->prim != NULL){
         lista->prim->ant = nova;
      }

      else {
         lista->ult = nova;
      }

      lista->prim = nova;
      nova->ant = NULL;
   }
}

/*
 * Busca um leitor na lista indicada.
 * Inputs: ponteiro para a lista, ID do leitor a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o leitor existem (estão alocados)
 * Pos-condicao: se o litor foi encontrado, retorna o ponteiro para ele, se não, retorna NULL
*/
void *BuscaListaLeitor(tLista *lista, int id){
   tCelula *aux;
   int idAux;
   aux = lista->prim;

   while(aux != NULL){
      idAux = GetIdLeitor(aux->info);

      if (idAux == id){
         return aux;
      }

      aux = aux->prox;
   }

   return NULL;
}

/*
 * Busca um livro na lista indicada.
 * Inputs: ponteiro para a lista, ID do livro a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o livro existem (estão alocados)
 * Pos-condicao: se o livro foi encontrado, retorna o ponteiro para ele, se não, retorna NULL
*/
void *BuscaListaLivro(tLista *lista, int id){
   tCelula *aux;
   int idAux;
   aux = lista->prim;

   while(aux != NULL){
      idAux = GetIdLivro(aux->info);

      if (idAux == id){
         return aux;
      }

      aux = aux->prox;
   }

   return NULL;
}

/*
 * Retira um leitor da lista indicada.
 * Inputs: ponteiro para a lista, ID do leitor a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o leitor existem (estão alocados)
 * Pos-condicao: se o leitor foi encontrado, retira o leitor da lista, se não, a lista permanece inalterada
*/
void RetiraListaLeitor(tLista *lista, int id){
   tCelula *aux;

   aux = BuscaListaLeitor(lista, id);

   if (aux != NULL){
      if (aux->ant == NULL){ // Verifica se e o primeiro da lista
         lista->prim = aux->prox;

         if (lista->prim != NULL){
            lista->prim->ant = NULL;
         }

         else {
            lista->ult = NULL; // Lista ficou vazia
         }
      }

      else if (aux->prox == NULL){ // Verifica se é o último da lista
         lista->ult = aux->ant;

         if (lista->ult != NULL){
            lista->ult->prox = NULL;
         }

         else {
            lista->prim = NULL; // Lista ficou vazia
         }
      }

      else { // Retira elemento do meio da lista
         aux->ant->prox = aux->prox;
         aux->prox->ant = aux->ant;
      }
      
      //return aux; // talvez a gnt deva usar um return para caso precisarmos desse livro;
      //free(aux); // comentei para podermos usar um livro mais de uma vez, se vc da um free aqui ela para de existir em outras listas
   }
}

/*
 * Retira um livro da lista indicada.
 * Inputs: ponteiro para a lista, ID do livro a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o livro existem (estão alocados)
 * Pos-condicao: se o livro foi encontrado, retira o livro da lista, se não, a lista permanece inalterada
*/
void RetiraListaLivro(tLista *lista, int id){
   tCelula *aux;

   aux = BuscaListaLivro(lista, id);

   if (aux != NULL){
      if (aux->ant == NULL){ // Verifica se e o primeiro da lista
         lista->prim = aux->prox;

         if (lista->prim != NULL){
            lista->prim->ant = NULL;
         }

         else {
            lista->ult = NULL; // Lista ficou vazia
         }
      }

      else if (aux->prox == NULL){ // Verifica se é o último da lista
         lista->ult = aux->ant;

         if (lista->ult != NULL){
            lista->ult->prox = NULL;
         }

         else {
            lista->prim = NULL; // Lista ficou vazia
         }
      }

      else { // Retira elemento do meio da lista
         aux->ant->prox = aux->prox;
         aux->prox->ant = aux->ant;
      }
      
      //return aux; // talvez a gnt deva usar um return para caso precisarmos desse livro;
      //free(aux); // comentei para podermos usar um livro mais de uma vez, se vc da um free aqui ela para de existir em outras listas
   }
}

/*
 * Imprime uma lista de leitores.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeListaLeitor(tLista *lista){
   tCelula *aux;
   aux = lista->prim;

   while(aux != NULL){
      ImprimeLeitor(aux->info);
      aux = aux->prox;
   }
}

/*
 * Imprime uma lista de livros.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeListaLivro(tLista *lista){
   tCelula *aux;
   aux = lista->prim;

   while(aux != NULL){
      ImprimeLeitor(aux->info);
      aux = aux->prox;
   }
}

/*
 * Libera a memória de uma lista de leitores.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: memórias da lista e dos seus elementos liberadas
*/
void LiberaListaLeitor(tLista *lista){
   tCelula *aux;
   aux = lista->prim;

   if (lista != NULL){

      while(1){
         LiberaLeitor(aux->info);
      
         if (aux->prox != NULL){
            aux = aux->prox;
            free(aux->ant);
         }

         else {
            free(aux);
            break;
         }
      }
   }
}

/*
 * Libera a memória de uma lista de livros.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: memórias da lista e dos seus elementos liberadas
*/
void LiberaListaLivro(tLista *lista){
   tCelula *aux;
   aux = lista->prim;

   if (lista != NULL){

      while(1){
         LiberaLivro(aux->info);
      
         if (aux->prox != NULL){
            aux = aux->prox;
            free(aux->ant);
         }

         else {
            free(aux);
            break;
         }
      }
   }
}