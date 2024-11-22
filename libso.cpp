#include "libso.h"

float media(int n, Processo processos[]) {
    float somaEspera = 0;
    for(int i = 0; i < n; i++) {
        somaEspera += processos[i].tempoEspera;
    }
    return somaEspera / n;
}

void printGanttChart(int n, Processo processos[]) {

    cout << "\nDiagrama de Gantt\n";
    int totalTime = 0, i = 0, j = 0;

    for ( i = 0; i < n; i++) {
        totalTime += processos[i].tempoExecucao;
    }

    cout << "     ";
    for ( i = 0; i <= totalTime; i += 5) {
        cout << i << setw(10);
    }
    cout << "\n";

    sort(processos, processos + n, [](Processo a, Processo b) { return a.id < b.id; });

    for ( i = 0; i < n; i++) {
        cout << "P" << processos[i].id << " | ";

        cout << setw(processos[i].tempoEspera * 2) << "";  

        for ( j = 0; j < processos[i].tempoExecucao * 2; j++) { 
            cout << "■";
        }
        cout << endl;
    }
}
