
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "libso.h"
using namespace std;

int main() {
    int n = 5;           
    int quantum = 10;    
    Processo processos[n];
    vector<string> gantt;  // Para armazenar a ordem dos processos no Gantt
    vector<int> tempos;    // Para armazenar os tempos de execução
    int tempoAtual = 0;    // Tempo total acumulado
    int finalizado = 0;    // Contador de processos finalizados

    // Entrada dos tempos de execução
    cout << "Insira o tempo de execução dos processos:" << endl;
    for (int i = 0; i < n; i++) {
        processos[i].id = i + 1;
        cout << "P" << processos[i].id << ": ";
        cin >> processos[i].tempoExecucao;
    }

    cout << "\nDiagrama de Gantt para Round Robin\n";

    // Criação de variáveis para controle de execução
    int temposRestantes[n];
    for (int i = 0; i < n; i++) {
        temposRestantes[i] = processos[i].tempoExecucao; // Copia os tempos de execução
    }

    while (finalizado < n) {
        for (int i = 0; i < n; i++) {
            if (temposRestantes[i] > 0) { // Se o processo ainda não foi concluído
                int tempoExec = min(quantum, temposRestantes[i]); // Executa pelo quantum ou pelo tempo restante
                temposRestantes[i] -= tempoExec;
                tempoAtual += tempoExec;
                gantt.push_back("P" + to_string(processos[i].id)); // Adiciona ao Gantt
                tempos.push_back(tempoAtual);                     // Marca o tempo final deste processo

                // Incrementa o tempo de espera para outros processos
                for (int j = 0; j < n; j++) {
                    if (j != i && temposRestantes[j] > 0) {
                        processos[j].tempoEspera += tempoExec;
                    }
                }

                // Se o processo foi finalizado, incrementa o contador
                if (temposRestantes[i] == 0) {
                    finalizado++;
                }
            }
        }
    }

    // Imprime o diagrama de Gantt
    cout << " ";
    for (int i = 0; i < gantt.size(); i++) {
        cout << "----";
    }
    cout << "\n|";
    for (int i = 0; i < gantt.size(); i++) {
        cout << setw(2) << gantt[i] << " |";
    }
    cout << "\n ";
    for (int i = 0; i < gantt.size(); i++) {
        cout << "----";
    }
    cout << "\n0";
    for (int i = 0; i < tempos.size(); i++) {
        cout << setw(4) << tempos[i];
    }
    cout << endl;

    return 0;
}

