#include "libso.h"

int main() {
    int n = 5, i = 0;
    float tempoEspera = 0;
    Processo p[n];
    cout << "Prioridades\nInsira o tempo dos processos:\n";

    for ( i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "P" << p[i].id << ": ";
        cin >> p[i].tempoExecucao;
    }
    cout << "\nInsira a prioridade dos processos:\n";

    for ( i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "P" << p[i].id << ": ";
        cin >> p[i].prioriade;
    }
    sort(p, p + n, [](Processo a, Processo b) { return a.prioriade < b.prioriade; });

    cout << "Processo\tTempo de execução\tTempo de espera\n";
    for ( i = 0; i < n; i++) {
        p[i].tempoEspera = tempoEspera;
        cout << "P" << p[i].id << "\t\t" << p[i].tempoExecucao << "\t\t\t" << p[i].tempoEspera << endl;
        tempoEspera += p[i].tempoExecucao;
    }

    cout << "Tempo médio de espera: " << media(n, p) << endl;

    printGanttChart(n, p);

    return 0;
}