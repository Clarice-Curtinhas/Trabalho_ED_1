/**
 * Created by Clarice Curtinhas Santos on 6/6/25
 * Copyright © 2025 Clarice Curtinhas Santos, Ana Luisa Casotti de Andrade. All rights reserved.
 */

#ifndef LIVRO_H
#define LIVRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livro tLivro;

/*
 * Cadastra um livro novo no sistema "BookED!" a partir das informações passadas.
 * Inputs: ID, título, autor, gênero e ano do livro
 * Outputs: um tipo "tLivro" alocado e com os campos preenchidos
 */
tLivro *CadastraLivro(int id, char *titulo, char *autor, char *genero, int ano);

/*
 * Retorna o ID de um livro.
 * Inputs: ponteiro para um elemento do tipo "tLivro"
 * Outputs: o ID(int) do livro passado como parâmetro
 */
int GetIdLivro(tLivro *livro);

/*
 * Retorna o nome de um livro.
 * Inputs: ponteiro para um elemento do tipo "tLivro"
 * Outputs: o nome (string/char*) do livro passado como parâmetro
 */
char *GetNomeLivro(tLivro *livro);

/*
 * Imprime o título de um único livro.
 * Inputs: ponteiro para um elemento do tipo "tLivro"
 * Outputs: nenhum
 */
void ImprimeLivro(tLivro *livro);

/*
 * Libera a memória de um único livro.
 * Inputs: ponteiro para um elemento do tipo "tLivro"
 * Outputs: nenhum
 */
void LiberaLivro(tLivro *livro);

#endif