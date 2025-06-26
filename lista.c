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
void InsereElementoLista(tLista *lista, void *elemento){
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

void InsereStringLista(tLista *lista, char *genero){
   tCelula *nova = (tCelula*) calloc(1, sizeof(tCelula));

   if (genero != NULL){
      nova->info = strdup(genero);
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
 * Inputs: ponteiro para a lista, leitor a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o leitor existem (estão alocados)
 * Pos-condicao: se o leitor foi encontrado, retorna o ponteiro para ele, se não, retorna NULL
*/
int ProcuraCelulaLeitor(tLista *lista, tLeitor *leitor1, tLeitor *leitor2, tLista *analisadas){
   tCelula *aux, *ajud;
   tLeitor *novoLeitor;

   aux = lista->prim;

   while(aux != NULL){
      if (aux->info == leitor2){
         return 1;
      }

      aux = aux->prox;
   }

   return 0;
}

/*
 * Busca um leitor diferente do que já está sendo usado na lista indicada.
 * Inputs: ponteiro para a lista, leitor usado
 * Outputs: nenhum
 * Pre-condicao: a lista e o leitor existem (estão alocados)
 * Pos-condicao: se um leitor diferente for encontrado, retorna o ponteiro para ele, se não, retorna o leitor antigo
*/
tLeitor *RetornaCelulaDiferente(tLista *lista, tLista *analisadas){
   tCelula *aux, *ajud;
   int jaExiste;
   aux = lista->prim;

   while(aux != NULL){
      jaExiste = 0;
      ajud = analisadas->prim;

      while(ajud != NULL){
         if((tLeitor*)aux->info == (tLeitor*)ajud->info){
            jaExiste = 1;
            break;
         }

         ajud = ajud->prox;
      }

      if(jaExiste == 0) return (tLeitor*)aux->info;

      aux = aux->prox;
   }

   return NULL;
}

/*
 * Compara as informações de duas listas de strings, para ver se existe uma info igual.
 * Inputs: ponteiro para a primrira lista e para a segunda lista que vão ser comparadas.
 * Outputs: 1 caso eles tenham informações que se repetem e 0, caso contrário.
 * Pre-condicao: as listas existem (estão alocados)
 * Pos-condicao: se a informação foi encontrado ou não, retorna os valores 1 ou 0, respectivamente
*/
int ComparaListasStrings(tLista *lista1, tLista *lista2){
   tCelula *aux, *ajud;

   for(aux = lista1->prim; aux != NULL; aux = aux->prox){
      for(ajud = lista2->prim; ajud != NULL; ajud = ajud->prox){
         if(strcmp((char*)aux->info, (char*)ajud->info) == 0) return 1;
      }
   }

   return 0;
}

/*
 * Busca um leitor na lista indicada.
 * Inputs: ponteiro para a lista, ID do leitor a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o leitor existem (estão alocados)
 * Pos-condicao: se o litor foi encontrado, retorna o ponteiro para ele, se não, retorna NULL
*/
tCelula *BuscaListaLeitor(tLista *lista, int id){
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
 * Retorna a informação de uma celula
 * Inputs: ponteiro para uma celula
 * Outputs: a informação
 * Pre-condicao: a celula existe (está alocada)
 * Pos-condicao: a informação dentro da celula
*/
tLeitor *InfoCelulaLeitor(tCelula *cel){
   if(cel != NULL) return cel->info;
   else return NULL;
}

/*
 * Busca um livro na lista indicada.
 * Inputs: ponteiro para a lista, ID do livro a ser procurado
 * Outputs: nenhum
 * Pre-condicao: a lista e o livro existem (estão alocados)
 * Pos-condicao: se o livro foi encontrado, retorna o ponteiro para ele, se não, retorna NULL
*/
tCelula *BuscaListaLivro(tLista *lista, int id){
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
 * Retorna a informação de uma celula
 * Inputs: ponteiro para uma celula
 * Outputs: a informação
 * Pre-condicao: a celula existe (está alocada)
 * Pos-condicao: a informação dentro da celula
*/
tLivro *InfoCelulaLivro(tCelula *cel){
   if(cel != NULL) return cel->info;
   else return NULL;
}

/*
 * Compara as informações de duas listas, para ver se existe uma info igual.
 * Inputs: ponteiro para a primrira lista e para a segunda lista que vão ser comparadas.
 * Outputs: a informação, caso eles tenham informações que se repetem e NULL, caso contrário.
 * Pre-condicao: as listas existem (estão alocados)
 * Pos-condicao: se a informação foi encontrado ou não, retorna a própria info ou NULL, respectivamente
*/
tLivro *ProcuraCelulaEmComum(tLista *lista1, tLista *lista2){
   tCelula *aux, *ajud;

   for(aux = lista1->prim; aux != NULL; aux = aux->prox){
      for(ajud = lista2->prim; ajud != NULL; ajud = ajud->prox){
         if((tLivro*)aux->info == (tLivro*)ajud->info) return (tLivro*)aux->info;
      }
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

      free(aux);
   }
}

/*
 * Imprime uma lista de leitores.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeListaLeitor(tLista *lista, FILE *saida){
   tCelula *aux;
   aux = lista->ult;

   while(aux != NULL){
      ImprimeLeitor(aux->info, saida);
      aux = aux->ant;
      fprintf(saida, "\n\n");
   }
}

/*
 * Imprime os nomes dos leitores.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeListaNomesLeitores(tLista *lista, FILE *saida){
   tCelula *aux;
   int start = 0;

   aux = lista->ult;

   while(aux != NULL){
      if(start == 1) fprintf(saida, ", ");

      fprintf(saida, "%s", GetNomeLeitor(aux->info));
      aux = aux->ant;

      start = 1;
   }
}

/*
 * Imprime uma lista de livros.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeListaLivro(tLista *lista, FILE *saida){
   tCelula *aux;
   int start = 0;

   aux = lista->ult;

   while(aux != NULL){
      if(start == 1) fprintf(saida, ", ");

      fprintf(saida, "%s", GetNomeLivro(aux->info));
      aux = aux->ant;
      start = 1;
   }
}

/*
 * Imprime uma lista de strings.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeListaStrings(tLista *lista){
   tCelula *aux;
   aux = lista->prim;

   while(aux != NULL){
      printf("%s ", (char*)aux->info);
      aux = aux->prox;
   }
}

/*
 * Libera a memória de uma lista de Strings.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: memórias da lista e dos seus elementos liberadas
*/
void LiberaListaString(tLista *lista){
   tCelula *aux;
   aux = lista->prim;

   if (lista != NULL && aux != NULL){

      while(1){
         free(aux->info);
      
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

   free(lista);
}

/*
 * Libera a memória de uma lista de celulas.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 * Pre-condicao: a lista existe (está alocada)
 * Pos-condicao: memórias da lista e dos seus elementos liberadas
*/
void LiberaCelulas(tLista *lista){
   tCelula *aux;
   aux = lista->prim;

   if (lista != NULL && aux != NULL){
      while(1){      
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

   free(lista);
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

   if (lista != NULL && aux != NULL){

      while(1){
         DesalocaLeitor(aux->info);
      
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

   free(lista);
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

   if (lista != NULL && aux != NULL){

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

   free(lista);
}