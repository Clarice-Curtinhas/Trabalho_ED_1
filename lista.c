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
 */
tLista *CriaLista(){
   tLista *lista = (tLista*) calloc(1, sizeof(tLista));

   lista->prim = NULL;
   lista->ult = NULL;

   return lista;
}

/*
 * Insere um novo elemento no final da lista.
 * Inputs: ponteiro para a lista onde será inserido o elemento, ponteiro para o elemento a ser inserido, tipo do elemento
 * Outputs: nenhum
 */
void InsereElementoLista(tLista *lista, void *elemento, int tipo){
   tCelula *nova = (tCelula*) calloc(1, sizeof(tCelula));

   nova->tipo = tipo;

   if (elemento != NULL){
      if (nova->tipo == STRING){
         nova->info = strdup(elemento);
      }

      else {
         nova->info = elemento;
      }
      
      nova->ant = lista->ult;

      if (lista->ult != NULL){
         lista->ult->prox = nova;
      }

      else {
         lista->prim = nova;
      }

      lista->ult = nova;
      nova->prox = NULL;
   }

   else {
      free(nova);
   }
}

/*
 * Retorna a informação de uma célula
 * Inputs: ponteiro para uma célula
 * Outputs: a informação
 */
void *GetInfoCelula(tCelula *cel){
   if(cel != NULL) return cel->info;
   else return NULL;
}

/*
 * Retorna a primeira celula da lista
 * Inputs: ponteiro para uma lista
 * Outputs: a priemira célula
 */
tCelula *GetPrimeiraCelula(tLista *lista){
   return lista->prim;
}

/*
 * Retorna a próxima celula a partir da célula passada
 * Inputs: ponteiro para uma celula
 * Outputs: a próxima célula
 */
tCelula *GetProximaCelula(tCelula *celula){
   return celula->prox;
}

/*
 * Busca um elemento na lista indicada.
 * Inputs: ponteiro para a lista, ID do elemento a ser procurado
 * Outputs: nenhum
 */
tCelula *BuscaElementoLista(tLista *lista, int id){
   tCelula *aux;
   int idAux;
   aux = lista->prim;

   while(aux != NULL){

      if (aux->tipo == LEITOR){
         idAux = GetIdLeitor(aux->info);
      }

      else if (aux->tipo == LIVRO){
         idAux = GetIdLivro(aux->info);
      }

      if (idAux == id){
         return aux;
      }

      aux = aux->prox;
   }

   return NULL;
}

/*
 * Retira um elemento da lista indicada.
 * Inputs: ponteiro para a lista, ID do elemento a ser procurado
 * Outputs: nenhum
 */
void RetiraElementoLista(tLista *lista, int id){
   tCelula *aux;

   aux = BuscaElementoLista(lista, id);

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
      
      free(aux); // Libera só a célula, não a informação dela
   }
}

/*
 * Compara as informações de duas listas de strings, para ver se existe uma info igual.
 * Inputs: ponteiro para a primrira lista e para a segunda lista que vão ser comparadas.
 * Outputs: 1 caso eles tenham informações que se repetem e 0, caso contrário.
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
 * Compara duas listas de afinidade para ver se existe uma info igual.
 * Inputs: ponteiros para a primeira e para a segunda lista que vão ser comparadas.
 * Outputs: 1 caso eles tenham informações que se repetem e 0, caso contrário.
 */
int TemAfinidade(tLista *afinidades1, tLista *afinidades2){
   tCelula *aux1, *aux2;
   int id1, id2;
   aux1 = afinidades1->prim;
   aux2 = afinidades2->prim;

   while (aux1 != NULL){
      id1 = GetIdLeitor(aux1->info);

      while (aux2 != NULL){
         id2 = GetIdLeitor(aux2->info);

         if (id1 == id2){
            return 1;
         }

         aux2 = aux2->prox;
      }

      aux2 = afinidades2->prim;
      aux1 = aux1->prox;
   }

   return 0;
}

/*
 * Imprime apenas os elementos em comum entre duas listas. Usado apenas para livros.
 * Inputs: ponteiro para a lista, arquivo de saida
 * Outputs: nenhum
 */
void ImprimeCelulasEmComum(tLista *lista1, tLista *lista2, FILE *saida){
   tLista *livrosEmComum = CriaLista();
   tCelula *aux1, *aux2;

   int qtd = 0;

   for(aux1 = lista1->prim; aux1 != NULL; aux1 = aux1->prox){
      for(aux2 = lista2->prim; aux2 != NULL; aux2 = aux2->prox){
         if(GetIdLivro(aux1->info) == GetIdLivro(aux2->info)) {
            InsereElementoLista(livrosEmComum, aux1->info, LIVRO);
            qtd++;
         }
      }
   }

   if (qtd == 0) fprintf(saida, "Nenhum livro em comum");
   else ImprimeLista(livrosEmComum, saida);
   fprintf(saida, "\n");
   LiberaCelulas(livrosEmComum);
}

/*
 * Imprime uma lista.
 * Inputs: ponteiro para a lista, arquivo de saida
 * Outputs: nenhum
 */
void ImprimeLista(tLista *lista, FILE *saida){
   tCelula *aux;
   int start = 0;
   aux = lista->prim;

   while(aux != NULL){
      if (aux->tipo == LEITOR){
         ImprimeLeitor(aux->info, saida);
         fprintf(saida, "\n\n");
      }

      else if (aux->tipo == LIVRO){
         if(start == 1) fprintf(saida, ", ");
         ImprimeLivro(aux->info, saida);
         start = 1;
      }
      
      aux = aux->prox;
   }
}

/*
 * Imprime os nomes dos leitores.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void ImprimeListaNomesLeitores(tLista *lista, FILE *saida){
   tCelula *aux;
   int start = 0;

   aux = lista->prim;

   while(aux != NULL){
      if(start == 1) fprintf(saida, ", ");

      fprintf(saida, "%s", GetNomeLeitor(aux->info));
      aux = aux->prox;

      start = 1;
   }
}

/*
 * Libera a apenas a memória das celulas de uma lista.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void LiberaCelulas(tLista *lista){
   tCelula *aux;

   if (lista == NULL) return;

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
 * Libera a memória de uma lista (células e informações das células).
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void LiberaLista(tLista *lista){
   tCelula *aux;

   if (lista == NULL) return;

   aux = lista->prim;

   if (aux != NULL){

      while(1){
         if (aux->tipo == LEITOR){
            if (aux->info != NULL) DesalocaLeitor(aux->info);
         }

         else if (aux->tipo == LIVRO){
            if (aux->info != NULL) LiberaLivro(aux->info);
         }

         else if (aux->tipo == STRING){
            if (aux->info != NULL) free(aux->info);
         }
         
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