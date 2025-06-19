/**
 * Created by Clarice Curtinhas Santos on 6/6/25
 * Copyright © 2025 Clarice Curtinhas Santos, Ana Luisa Casotti de Andrade. All rights reserved.
 */

#include "leitor.h"
#include "lista.h"

#define TRUE 1
#define FALSE 0

typedef struct Leitor{
    int id;
    char *nome;
    tLista *generos; //lista para guardar qual as preferências de leitura de cada leitor
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

    l->generos = CriaLista();
    l->lidos = CriaLista();
    l->desejados = CriaLista();
    l->recomendacoes = CriaLista();
    l->afinidades = CriaLista();

    return l;
}

void AdicionarGenero(tLeitor *leitor, char *genero){
    InsereStringLista(leitor->generos, genero);
}

void AssociaLeitores(tLeitor *leitor1, tLeitor *leitor2){
    if(leitor1 != NULL && leitor2 != NULL){
        if(ComparaListasStrings(leitor1->generos, leitor2->generos) == TRUE){
            InsereLeitorLista(leitor1->afinidades, leitor2);
            InsereLeitorLista(leitor2->afinidades, leitor1);
        }
    }
}

void AdicionarLivroLido(tLeitor *leitor, tLivro *livro){
    InsereLivroLista(leitor->lidos, livro);
}

void AdicionarLivroDesejado(tLeitor *leitor, tLivro *livro){
    InsereLivroLista(leitor->desejados, livro);
}

void RecomendarLivro(tLeitor *leitorOrig, int id, tLeitor *leitorDest){
    tLivro *livro;

    livro = InfoCelulaLivro(BuscaListaLivro(leitorOrig->lidos, id));
    //USEI UMA FUNÇÃO DENTRO DA OUTRA MUITAS VEZES
    //VER SE NÃO É MELHOR JUNTAR AS DUAS FUNÇÕES EM UMA SÓ 
            //(n sei se vai usar elas separadas em outra parte do código)

    InsereLivroLista(leitorDest->recomendacoes, livro);
}

void AceitarRecomendacao(tLeitor *leitor, tLivro *livro, int acao){
    if(acao == TRUE){
        InsereLivroLista(leitor->desejados, livro);
    }

    else{
        RetiraListaLivro(leitor->recomendacoes, GetIdLivro(livro));
        // ATENÇÃO: FAZER O RETIRA COM O GET ID É MAIS CUSTOSO PENSAR EM FAZER UMA FUNÇÃO QUE RETIRE DE FORMA DIRETA
    }
}

void RemoverRecomendacao(tLeitor *leitor, tLivro *livro){
    RetiraListaLivro(leitor->recomendacoes, GetIdLivro(livro));
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

char *GetNomeLeitor(tLeitor *leitor){
    return leitor->nome;
}

void ImprimeLeitor(tLeitor *leitor){
    printf("Leitor: %s\n", leitor->nome);
    printf("Lidos: ");
    ImprimeListaLivro(leitor->lidos);
    printf("\nDesejados: ");
    ImprimeListaLivro(leitor->desejados);
    printf("\nRecomendacoes: ");
    ImprimeListaLivro(leitor->recomendacoes);
    printf("\nAfinidades: ");
    ImprimeListaNomesLeitores(leitor->afinidades);
}

void DesalocaLeitor(tLeitor *leitor){
    LiberaListaLivro(leitor->afinidades);
    LiberaListaLivro(leitor->desejados);
    LiberaListaLivro(leitor->lidos);
    LiberaListaLivro(leitor->recomendacoes);
    LiberaListaString(leitor->generos);

    free(leitor);
}