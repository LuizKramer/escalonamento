#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include "libso.h"

using namespace std;

int main() {
    int n = 5, i = 0, j = 0, quantum = 1, tempoAtual = 0, finalizado = 0, somaEspera = 0, somaRetorno = 0;
    Processo processos[n];
    vector<string> gantt;  // Para armazenar a ordem dos processos no Gantt
    vector<int> tempos;    // Para armazenar os tempos de execução

    // Entrada dos tempos de execução
    cout << "Insira o tempo de execução dos processos:" << endl;
    for ( i = 0; i < n; i++) {
        processos[i].id = i + 1;
        cout << "P" << processos[i].id << ": ";
        cin >> processos[i].tempoExecucao;
    }

    cout << "\nDiagrama de Gantt para Round Robin\n";

    // Criação de variáveis para controle de execução
    int temposRestantes[n];
    for ( i = 0; i < n; i++) {
        temposRestantes[i] = processos[i].tempoExecucao; // Copia os tempos de execução
    }

    while (finalizado < n) {
        for ( i = 0; i < n; i++) {
            if (temposRestantes[i] > 0) { // Se o processo ainda não foi concluído
                int tempoExec = min(quantum, temposRestantes[i]); // Executa pelo quantum ou pelo tempo restante
                temposRestantes[i] -= tempoExec;
                tempoAtual += tempoExec;
                gantt.push_back("P" + to_string(processos[i].id)); // Adiciona ao Gantt
                tempos.push_back(tempoAtual);                     // Marca o tempo final deste processo

                // Incrementa o tempo de espera para outros processos
                for ( j = 0; j < n; j++) {
                    if (j != i && temposRestantes[j] > 0) {
                        processos[j].tempoEspera += tempoExec;
                    }
                }

                // Se o processo foi finalizado, calcula tempo de retorno
                if (temposRestantes[i] == 0) {
                    processos[i].tempoRetorno = tempoAtual;
                    finalizado++;
                }
            }
        }
    }

    // Imprime o diagrama de Gantt
    cout << " ";
    for ( i = 0; i < gantt.size(); i++) {
        cout << "----";
    }
    cout << "\n|";
    for ( i = 0; i < gantt.size(); i++) {
        cout << setw(2) << gantt[i] << " |";
    }
    cout << "\n ";
    for ( i = 0; i < gantt.size(); i++) {
        cout << "----";
    }
    cout << "\n0";
    for ( i = 0; i < tempos.size(); i++) {
        cout << setw(4) << tempos[i];
    }
    cout << endl;

    // Calcula os tempos médios
    for ( i = 0; i < n; i++) {
        somaEspera += processos[i].tempoEspera;
        somaRetorno += processos[i].tempoRetorno;
    }

    cout << "\nTempo médio de espera: " << fixed << setprecision(2) << (float)somaEspera / n << " unidades\n";

    return 0;
}
