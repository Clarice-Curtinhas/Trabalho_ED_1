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
            InsereElementoLista(leitor1->afinidades, leitor2);
            InsereElementoLista(leitor2->afinidades, leitor1);

            DefineTipoLeitor(leitor1->afinidades);
            DefineTipoLeitor(leitor2->afinidades);   
        }
    }
}

void AdicionarLivroLido(tLeitor *leitor, tLivro *livro){
    InsereElementoLista(leitor->lidos, livro);
    DefineTipoLivro(leitor->lidos);
}

void AdicionarLivroDesejado(tLeitor *leitor, tLivro *livro){
    InsereElementoLista(leitor->desejados, livro);
    DefineTipoLivro(leitor->lidos);
}

int RecebeRecomendacaoLivro(tLivro *livro, tLeitor *leitor){
    if(BuscaElementoLista(leitor->lidos, GetIdLivro(livro)) != NULL) return 1;

    else{
        InsereElementoLista(leitor->recomendacoes, livro);
        DefineTipoLivro(leitor->recomendacoes);
        return 0;
    }
}

int LivroExisteNosDadosDoLeitor(tLeitor *leitor, int id, int lista){
    tLivro *livro;

    if(lista == 1) livro = InfoCelulaLivro(BuscaElementoLista(leitor->lidos, id));
    else if(lista == 2) livro = InfoCelulaLivro(BuscaElementoLista(leitor->desejados, id));
    else if(lista == 3) livro = InfoCelulaLivro(BuscaElementoLista(leitor->recomendacoes, id));

    if(livro != NULL){
        return TRUE;
    }
    else return FALSE;
}

void AceitarRecomendacao(tLeitor *leitor, tLivro *livro, int acao){
    if(acao == TRUE){
        InsereElementoLista(leitor->desejados, livro);
        DefineTipoLivro(leitor->desejados);
        RetiraElementoLista(leitor->recomendacoes, GetIdLivro(livro));
    }

    else{
        RetiraElementoLista(leitor->recomendacoes, GetIdLivro(livro));
        // ATENÇÃO: FAZER O RETIRA COM O GET ID É MAIS CUSTOSO PENSAR EM FAZER UMA FUNÇÃO QUE RETIRE DE FORMA DIRETA
    }
}

int ProcuraLivrosEmComum(tLeitor *leitor1, tLeitor *leitor2, tLista *livrosEmComum){

    ProcuraCelulasEmComum(leitor1->lidos, leitor2->lidos, livrosEmComum);

}

void ImprimeLivrosEmComum(tLeitor *leitor1, tLeitor *leitor2, FILE *saida){
    ImprimeCelulasEmComum(leitor1->lidos, leitor2->lidos, saida);
}

/*int VerificaAfinidade(tLeitor *leitor1, tLeitor *leitor2){
    tLista *analisadas;
    tLeitor *novoLeitor;

    analisadas = CriaLista();

    if(ProcuraCelulaLeitor(leitor1->afinidades, leitor1, leitor2, analisadas) == TRUE){
        LiberaCelulas(analisadas);
        return TRUE;
    }

    else{
        InsereElementoLista(analisadas, leitor1);

        while((novoLeitor = RetornaCelulaDiferente(leitor1->afinidades, analisadas)) != NULL){
            if(ProcuraCelulaLeitor(novoLeitor->afinidades, novoLeitor, leitor2, analisadas) == TRUE){
                LiberaCelulas(analisadas);
                return TRUE;
            }

            InsereElementoLista(analisadas, novoLeitor);
        }
    }

    LiberaCelulas(analisadas);

    return FALSE;
}*/

int ExisteAfinidade(tLeitor *leitor1, tLeitor *leitor2){
    if (ProcuraCelulaLeitor(leitor1->afinidades, leitor2) == TRUE){
        return TRUE;
    }

    else {
        tCelula *aux;
        tLeitor *leitorAux;
        aux = GetPrimeiraCelula(leitor1->afinidades);
        leitorAux = InfoCelulaLeitor(aux);

        while(aux != NULL){
            if (ProcuraCelulaLeitor(leitorAux->afinidades, leitor2) == TRUE){
                return TRUE;
            }

            else {
                aux = GetProximaCelula(aux);
                leitorAux = InfoCelulaLeitor(aux);
            }
        }

        return FALSE;
    }
}
/*tLista *RecursaoAfinidades(tLeitor *leitor){
    return leitor->afinidades;
}*/

int GetIdLeitor(tLeitor *leitor){
    return leitor->id;
}

char *GetNomeLeitor(tLeitor *leitor){
    return leitor->nome;
}

void ImprimeLeitor(tLeitor *leitor, FILE *saida){
    fprintf(saida, "Leitor: %s\n", leitor->nome);
    fprintf(saida, "Lidos: ");
    ImprimeListaLivro(leitor->lidos, saida);
    fprintf(saida, "\nDesejados: ");
    ImprimeListaLivro(leitor->desejados, saida);
    fprintf(saida, "\nRecomendacoes: ");
    ImprimeListaLivro(leitor->recomendacoes, saida);
    fprintf(saida, "\nAfinidades: ");
    ImprimeListaNomesLeitores(leitor->afinidades, saida);
}

void DesalocaLeitor(tLeitor *leitor){
    LiberaCelulas(leitor->lidos);
    LiberaCelulas(leitor->desejados);
    LiberaCelulas(leitor->recomendacoes);
    LiberaListaString(leitor->generos);
    LiberaCelulas(leitor->afinidades);

    free(leitor->nome);
    free(leitor);
}