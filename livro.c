/**
 * Created by Clarice Curtinhas Santos on 6/6/25
 * Copyright © 2025 Clarice Curtinhas Santos, Ana Luisa Casotti de Andrade. All rights reserved.
 */

#include "livro.h"

struct Livro {
    int id;
    char *titulo;
    char *autor;
    char *genero;
    int ano;
};

/*
 * Cadastra um livro novo no sistema "BookED!" a partir das informações passadas.
 * Inputs: ID, título, autor, gênero e ano do livro
 * Outputs: um tipo "tLivro" alocado e com os campos preenchidos
 * Pre-condicao: nenhuma
 * Pos-condicao: um tipo "tLivro" alocado e com os campos preenchidos
*/
tLivro *CadastraLivro(int id, char *titulo, char *autor, char *genero, int ano){
    tLivro *livro = (tLivro*) calloc(1, sizeof(tLivro));

    livro->id = id;
    livro->titulo = strdup(titulo);
    livro->autor = strdup(autor);
    livro->genero = strdup(genero);
    livro->ano = ano;

    return livro;
}

/*
 * Retorna o ID de um livro.
 * Inputs: ponteiro para um elemento do tipo "tLivro"
 * Outputs: o ID(int) do livro passado como parâmetro
 * Pre-condicao: o livro passado tem os campos preechidos (ou seja, não está "vazio")
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
int GetIdLivro(tLivro *livro){
    return livro->id;
}

/*
 * Imprime o título de um único livro.
 * Inputs: ponteiro para um elemento do tipo "tLivro"
 * Outputs: nenhum
 * Pre-condicao: o livro passado tem os campos preechidos (ou seja, não está "vazio")
 * Pos-condicao: nenhuma alteração feita nos conteúdos das estruturas de dados
*/
void ImprimeLivro(tLivro *livro){
    printf("%s", livro->titulo);
}

/*
 * Libera a memória de um único livro.
 * Inputs: ponteiro para um elemento do tipo "tLivro"
 * Outputs: nenhum
 * Pre-condicao: o livro passado existe e tem os campos preechidos (ou seja, não está "vazio")
 * Pos-condicao: memória do livro passado liberada
*/
void LiberaLivro(tLivro *livro){
    if (livro != NULL){
        free(livro->titulo);
        free(livro->autor);
        free(livro->genero);
        free(livro);
    }
}