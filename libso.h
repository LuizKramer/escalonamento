#ifndef LIBSO_H
#define LIBSO_H

struct Processo {
    int id;
    int tempoExecucao;
    int tempoEspera;
};

float media(int n, Processo processos[]);

#endif
