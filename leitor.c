/**
 * Created by Clarice Curtinhas Santos on 6/6/25
 * Copyright © 2025 Clarice Curtinhas Santos. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livro.h"
#include "lista.h"

typedef struct Leitor{
    int id;
    char *nome;
    tLista *lidos;
    tLista *desejados;
    tLista *recomendacoes;
    tLista *afinidades;
} tLeitor;

tLeitor *CriaLeitor(char *nome){
    tLeitor *l;

    l = (tLeitor*) calloc(1, sizeof(tLeitor));

    l->nome = strdup(nome);

    l->lidos = CriaLista();
    l->desejados = CriaLista();
    l->recomendacoes = CriaLista();
    l->afinidades = CriaLista();

    return l;
}

void AdicionarLivroLido(tLeitor *leitor, tLivro *livro);

void AdicionarLivroDesejado(tLeitor *leitor, tLivro *livro);

void RecomendarLivro(tLeitor *leitorOrig, tLivro *livro, tLeitor *leitorDest);

void AceitarRecomendacao(tLeitor *leitorOrig, tLivro *livro, tLeitor *leitorDest);

void RemoverRecomendacao(tLeitor *leitorOrig, tLivro *livro, tLeitor *leitorDest);

tLivro *ProcuraLivroEmComum(tLeitor *leitor1, tLeitor *leitor2);

int VerificaAfinidade(tLeitor *leitor1, tLeitor *leitor2);

void ImprimeLeitor(tLeitor *leitor);

void DesalocaLeitor(tLeitor *leitor);