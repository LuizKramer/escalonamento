#include <iostream>
#include "libso.h"
using namespace std;

int main() {
    int n = 5, i = 0;
    float tempoEspera = 0;
    Processo p[n];
    
    cout << "Algoritmo First Come First Serve (FCFS)\nInsira o tempo dos processos:\n";

    for(i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "P" << p[i].id << ": ";
        cin >> p[i].tempoExecucao;
    }

    cout << "Processo\tTempo de execução\tTempo de espera\n";
    for(i = 0; i < n; i++) {
        p[i].tempoEspera = tempoEspera;
        cout << "P" << p[i].id << "\t\t" << p[i].tempoExecucao << "\t\t\t" << p[i].tempoEspera << endl;
        tempoEspera += p[i].tempoExecucao;
    }

    cout << "Tempo médio de espera: " << media(n, p) << endl;
    printGanttChart(n, p);

    return 0;
}
