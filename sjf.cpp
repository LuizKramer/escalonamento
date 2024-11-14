#include <iostream>
#include <algorithm>
#include <iomanip>
#include "libso.h"
using namespace std;

void printGanttChart(int n, Processo processos[]) {
    int totalTime = 0;

    // Calculate total time for proper scaling
    for (int i = 0; i < n; i++) {
        totalTime += processos[i].tempoExecucao;
    }

    // Print timeline intervals at the top (0, 5, 10, 15, etc.)
    cout << "     ";
    for (int i = 0; i <= totalTime; i += 5) {
        cout << i << setw(10);
    }
    cout << "\n";

    // Sort processes by their IDs for ordered display
    sort(processos, processos + n, [](Processo a, Processo b) { return a.id < b.id; });

    // Print each process line
    for (int i = 0; i < n; i++) {
        cout << "P" << processos[i].id << " | ";

        // Adjust spacing for the start time of the process
        cout << setw(processos[i].tempoEspera * 2) << "";  // Each unit of tempoEspera is scaled for spacing

        // Display the execution block for the process
        for (int j = 0; j < processos[i].tempoExecucao * 2; j++) {  // Scale execution time
            cout << "■";
        }
        cout << endl;
    }
}

int main() {
    int n = 5;
    Processo p[n];
    cout << "Shortest Job First (SJF)\nInsira o tempo dos processos:\n";

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "P" << p[i].id << ": ";
        cin >> p[i].tempoExecucao;
    }

    // Sort by execution time for SJF scheduling
    sort(p, p + n, [](Processo a, Processo b) { return a.tempoExecucao < b.tempoExecucao; });

    cout << "Processo\tTempo de execução\tTempo de espera\n";
    float tempoEspera = 0;
    for (int i = 0; i < n; i++) {
        p[i].tempoEspera = tempoEspera;
        cout << "P" << p[i].id << "\t\t" << p[i].tempoExecucao << "\t\t\t" << p[i].tempoEspera << endl;
        tempoEspera += p[i].tempoExecucao;
    }

    cout << "Tempo médio de espera: " << media(n, p) << endl;

    // Generate Gantt Chart
    printGanttChart(n, p);

    return 0;
}
