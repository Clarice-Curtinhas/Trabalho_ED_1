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
 * Insere um novo elemento no início da lista.
 * Inputs: ponteiro para a lista onde será inserido o elemento, ponteiro para o elemento a ser inserido
 * Outputs: nenhum
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

void DefineTipoLeitor(tLista *lista){
   lista->prim->tipo = LEITOR;
}

void DefineTipoLivro(tLista *lista){
   lista->prim->tipo = LIVRO;
}

/*
 * Busca um leitor na lista indicada.
 * Inputs: ponteiro para a lista, leitor a ser procurado
 * Outputs: nenhum
 */
int ProcuraCelulaLeitor(tLista *lista, tLeitor *leitor){
   tCelula *aux;

   aux = lista->prim;

   while(aux != NULL){
      if (aux->info == leitor){
         return 1;
      }

      aux = aux->prox;
   }

   return 0;
}

tCelula *GetPrimeiraCelula(tLista *lista){
   return lista->prim;
}

tCelula *GetProximaCelula(tCelula *celula){
   return celula->prox;
}

/*
 * Busca um leitor diferente do que já está sendo usado na lista indicada.
 * Inputs: ponteiro para a lista, leitor usado
 * Outputs: nenhum
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
 * Retorna a informação de uma celula
 * Inputs: ponteiro para uma celula
 * Outputs: a informação
 */
tLeitor *InfoCelulaLeitor(tCelula *cel){
   if(cel != NULL) return ((tLeitor*)cel->info);
   else return NULL;
}

/*
 * Retorna a informação de uma celula
 * Inputs: ponteiro para uma celula
 * Outputs: a informação
 */
tLivro *InfoCelulaLivro(tCelula *cel){
   if(cel != NULL) return cel->info;
   else return NULL;
}

/*
 * Compara as informações de duas listas, para ver se existe uma info igual.
 * Inputs: ponteiro para a primrira lista e para a segunda lista que vão ser comparadas.
 * Outputs: a informação, caso eles tenham informações que se repetem e NULL, caso contrário.
 */
int ProcuraCelulasEmComum(tLista *lista1, tLista *lista2, tLista *livrosEmComum){
   tCelula *aux, *ajud;
   int qtd = 0;

   for(aux = lista1->prim; aux != NULL; aux = aux->prox){
      for(ajud = lista2->prim; ajud != NULL; ajud = ajud->prox){
         if((tLivro*)aux->info == (tLivro*)ajud->info) {
            InsereElementoLista(livrosEmComum, (tLivro*)aux->info);
            qtd++;
         }
      }
   

   return qtd;
}
}

void ImprimeCelulasEmComum(tLista *lista1, tLista *lista2, FILE *saida){
   tLista *livrosEmComum = CriaLista();
   tCelula *aux, *ajud;
   int qtd = 0;

   for(aux = lista1->prim; aux != NULL; aux = aux->prox){
      for(ajud = lista2->prim; ajud != NULL; ajud = ajud->prox){
         if(GetIdLivro(aux->info) == GetIdLivro(ajud->info)) {
            InsereElementoLista(livrosEmComum, aux->info);
            qtd++;
         }
      }
   }

   if (qtd == 0) fprintf(saida, "Nenhum livro em comum");
   else ImprimeListaLivro(livrosEmComum, saida);
   fprintf(saida, "\n");
   LiberaCelulas(livrosEmComum);
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
      
      //return aux; // talvez a gnt deva usar um return para caso precisarmos desse livro;
      //free(aux); // comentei para podermos usar um livro mais de uma vez, se vc da um free aqui ela para de existir em outras listas
   }
}

/*
 * Imprime uma lista de leitores.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
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

   aux = lista->prim;

   while(aux != NULL){
      if(start == 1) fprintf(saida, ", ");

      fprintf(saida, "%s", GetNomeLivro(aux->info));
      aux = aux->prox;
      start = 1;
   }
}

/*
 * Imprime uma lista de strings.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
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
 * Libera a memória de uma lista.
 * Inputs: ponteiro para a lista
 * Outputs: nenhum
 */
void LiberaLista(tLista *lista){
   tCelula *aux;
   aux = lista->prim;

   if (lista != NULL && aux != NULL){

      while(1){
         if (aux->tipo == LEITOR){
            DesalocaLeitor(aux->info);
         }

         else if (aux->tipo == LIVRO){
            LiberaLivro(aux->info);
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