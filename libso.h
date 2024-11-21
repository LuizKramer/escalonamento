#ifndef LIBSO_H
#define LIBSO_H

#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;


struct Processo {
    int id;
    int tempoExecucao;
    float tempoEspera = 0;
    int prioriade;
};

float media(int n, Processo processos[]);
void printGanttChart(int n, Processo processos[]);
//printGanttChartRR(int n, Processo processos[], int quantum);

#endif
