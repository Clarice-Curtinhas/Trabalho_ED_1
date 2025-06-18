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
#include "lista.h"

typedef struct Leitor tLeitor;

/*
 * Cria um leitor novo no sistema "BookED!" a partir das informações passadas.
 * Inputs: uma string com o nome da pessoa, um int com o id da pessoa
 * Outputs: um tipo "tLeitor" alocado e com as listas criadas
 * Pre-condicao: nenhuma
 * Pos-condicao: um tipo "tLeitor" alocado e com as listas criadas
*/
tLeitor *CriaLeitor(char *nome, int id);

void AdicionarLivroLido(tLeitor *leitor, tLivro *livro);

void AdicionarLivroDesejado(tLeitor *leitor, tLivro *livro);

void RecomendarLivro(tLeitor *leitorOrig, tLivro *livro, tLeitor *leitorDest);

void AceitarRecomendacao(tLeitor *leitorOrig, tLivro *livro, int acao);

void RemoverRecomendacao(tLeitor *leitor, tLivro *livro);

tLivro *ProcuraLivroEmComum(tLeitor *leitor1, tLeitor *leitor2);

int VerificaAfinidade(tLeitor *leitor1, tLeitor *leitor2);

int GetIdLeitor(tLeitor *leitor);

void ImprimeLeitor(tLeitor *leitor);

void DesalocaLeitor(tLeitor *leitor);

 #endif