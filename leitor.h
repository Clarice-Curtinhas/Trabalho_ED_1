/**
 * Created by Clarice Curtinhas Santos on 6/6/25
 * Copyright © 2025 Clarice Curtinhas Santos,  Ana Luisa Casotti de Andrade. All rights reserved.
 */

#ifndef LEITOR_H
#define LEITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livro.h"

typedef struct Leitor tLeitor;

/*
 * Cria um leitor novo no sistema "BookED!" a partir das informações passadas.
 * Inputs: uma string com o nome da pessoa, um int com o id da pessoa
 * Outputs: um tipo "tLeitor" alocado e com as listas criadas
 * Pre-condicao: nenhuma
 * Pos-condicao: um tipo "tLeitor" alocado e com as listas criadas
*/
tLeitor *CriaLeitor(char *nome, int id);

void AdicionarGenero(tLeitor *leitor, char *genero);

void AssociaLeitores(tLeitor *leitor1, tLeitor *leitor2);

void AdicionarLivroLido(tLeitor *leitor, tLivro *livro);

void AdicionarLivroDesejado(tLeitor *leitor, tLivro *livro);

int RecebeRecomendacaoLivro(tLivro *livro, tLeitor *leitor);

int LivroExisteNosDadosDoLeitor(tLeitor *leitor, int id, int lista);

void AceitarRecomendacao(tLeitor *leitorOrig, tLivro *livro, int acao);

//int ProcuraLivrosEmComum(tLeitor *leitor1, tLeitor *leitor2, tLista *livrosEmComum);

void ImprimeLivrosEmComum(tLeitor *leitor1, tLeitor *leitor2, FILE *saida);

//int VerificaAfinidade(tLeitor *leitor1, tLeitor *leitor2);

int ExisteAfinidade(tLeitor *leitor1, tLeitor *leitor2);

//tLista *GetAfinidades(tLeitor *leitor);

int GetIdLeitor(tLeitor *leitor);

char *GetNomeLeitor(tLeitor *leitor);

void ImprimeLeitor(tLeitor *leitor, FILE *saida);

void DesalocaLeitor(tLeitor *leitor);

#endif