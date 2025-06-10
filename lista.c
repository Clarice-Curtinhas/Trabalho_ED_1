/**
 * Created by Clarice Curtinhas Santos on 6/6/25
 * Copyright © 2025 Clarice Curtinhas Santos. All rights reserved.
 */

 typedef struct Celula{
    int tipo;
    void *info;
    tCelula *prox;
    tCelula *ant;
 } tCelula;

 typedef struct Lista{
    tCelula *prim;
    tCelula *ult;
 } tLista;
