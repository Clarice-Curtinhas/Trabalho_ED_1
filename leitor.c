/**
 * Created by Clarice Curtinhas Santos on 6/6/25
 * Copyright © 2025 Clarice Curtinhas Santos, Ana Luisa Casotti de Andrade. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livro.h"
#include "lista.h"

#define TRUE 1
#define FALSE 0

typedef struct Leitor{
    int id;
    char *nome;
    tLista *lidos;
    tLista *desejados;
    tLista *recomendacoes;
    tLista *afinidades;
} tLeitor;

/*
 * Cria um leitor novo no sistema "BookED!" a partir das informações passadas.
 * Inputs: uma string com o nome da pessoa, um int com o id da pessoa
 * Outputs: um tipo "tLeitor" alocado e com as listas criadas
 * Pre-condicao: nenhuma
 * Pos-condicao: um tipo "tLeitor" alocado e com as listas criadas
*/
tLeitor *CriaLeitor(char *nome, int id){
    tLeitor *l;

    l = (tLeitor*) calloc(1, sizeof(tLeitor));

    l->nome = strdup(nome);
    l->id = id;

    l->lidos = CriaLista();
    l->desejados = CriaLista();
    l->recomendacoes = CriaLista();
    l->afinidades = CriaLista();

    return l;
}

void AdicionarLivroLido(tLeitor *leitor, tLivro *livro){
    InsereLista(leitor->lidos, livro);
}

void AdicionarLivroDesejado(tLeitor *leitor, tLivro *livro){
    InsereLista(leitor->desejados, livro);
}

void RecomendarLivro(tLeitor *leitorOrig, int id, tLeitor *leitorDest){
    tLivro *livro;

    livro = BuscaLista(leitorOrig->lidos, id);

    InsereLista(leitorDest->recomendacoes, livro);
}

void AceitarRecomendacao(tLeitor *leitor, tLivro *livro, int acao){
    if(acao == TRUE){
        InsereLista(leitor->desejados, livro);
    }

    else{
        RetiraLista(leitor->recomendacoes, GetIdLivro(livro));
        // ATENÇÃO: FAZER O RETIRA COM O GET ID É MAIS CUSTOSO PENSAR EM FAZER UMA FUNÇÃO QUE RETIRE DE FORMA DIRETA
    }
}

void RemoverRecomendacao(tLeitor *leitor, tLivro *livro){
    RetiraLista(leitor->recomendacoes, GetIdLivro(livro));
    // ATENÇÃO: FAZER O RETIRA COM O GET ID É MAIS CUSTOSO PENSAR EM FAZER UMA FUNÇÃO QUE RETIRE DE FORMA DIRETA
}

tLivro *ProcuraLivroEmComum(tLeitor *leitor1, tLeitor *leitor2){
    /*tLivro *livro;

    livro = ProcuraCelulaEmComum(leitor1->lidos, leitor2->lidos);

    return livro;*/
}

int VerificaAfinidade(tLeitor *leitor1, tLeitor *leitor2);

int GetIdLeitor(tLeitor *leitor){
    return leitor->id;
}

void ImprimeLeitor(tLeitor *leitor){
    printf("Leitor: %s\n", leitor->nome);
    printf("Lidos: ");
    ImprimeLista(leitor->lidos);
    printf("\nDesejados: ");
    ImprimeLista(leitor->desejados);
    printf("\nRecomendacoes: ");
    ImprimeLista(leitor->recomendacoes);
    printf("\nAfinidades: ");
    ImprimeLista(leitor->afinidades);
}

void DesalocaLeitor(tLeitor *leitor){
    LiberaLista(leitor->afinidades);
    LiberaLista(leitor->desejados);
    LiberaLista(leitor->lidos);
    LiberaLista(leitor->recomendacoes);

    free(leitor);
}