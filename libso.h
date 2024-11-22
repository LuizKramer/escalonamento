#ifndef LIBSO_H
#define LIBSO_H

#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Processo {
    int id;
    int tempoExecucao;
    int tempoRetorno = 0;
    float tempoEspera = 0;
    int prioriade;
};

float media(int n, Processo processos[]);
void printGanttChart(int n, Processo processos[]);

#endif
