
#include "libso.h"


int main() {
    int n = 5;
    Processo p[n];
    cout << "Shortest Job First (SJF)\nInsira o tempo dos processos:\n";

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "P" << p[i].id << ": ";
        cin >> p[i].tempoExecucao;
    }

    sort(p, p + n, [](Processo a, Processo b) { return a.tempoExecucao < b.tempoExecucao; });

    cout << "Processo\tTempo de execução\tTempo de espera\n";
    float tempoEspera = 0;
    for (int i = 0; i < n; i++) {
        p[i].tempoEspera = tempoEspera;
        cout << "P" << p[i].id << "\t\t" << p[i].tempoExecucao << "\t\t\t" << p[i].tempoEspera << endl;
        tempoEspera += p[i].tempoExecucao;
    }

    cout << "Tempo médio de espera: " << media(n, p) << endl;

    printGanttChart(n, p);

    return 0;
}
