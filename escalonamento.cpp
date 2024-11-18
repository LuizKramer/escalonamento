#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>


using namespace std;

struct Processo {
    int id;
    int tempo_execucao;
    int tempo_chegada;
    int prioridade;
    int tempo_espera;
    int tempo_turnaround;
};

// Função para calcular o tempo médio de espera para FCFS
void calcular_fcfs(vector<Processo> &processos) {
    int n = processos.size();
    int tempo_total_espera = 0;
    int tempo_decorrido = 0;

    for (int i = 0; i < n; i++) {
        processos[i].tempo_espera = max(0, tempo_decorrido - processos[i].tempo_chegada);
        tempo_decorrido += processos[i].tempo_execucao;
        tempo_total_espera += processos[i].tempo_espera;
    }

    cout << "FCFS - Tempo médio de espera: " << (float)tempo_total_espera / n << " unidades\n";
}

// Função para calcular o tempo médio de espera para SJF
void calcular_sjf(vector<Processo> &processos) {
    int n = processos.size();
    int tempo_total_espera = 0, tempo_decorrido = 0;
    vector<bool> concluido(n, false);

    for (int count_concluido = 0; count_concluido < n; count_concluido++) {
        int mais_curto = -1;

        for (int i = 0; i < n; i++) {
            if (!concluido[i] && processos[i].tempo_chegada <= tempo_decorrido) {
                if (mais_curto == -1 || processos[i].tempo_execucao < processos[mais_curto].tempo_execucao) {
                    mais_curto = i;
                }
            }
        }

        if (mais_curto == -1) {
            tempo_decorrido++;
            continue;
        }

        processos[mais_curto].tempo_espera = tempo_decorrido - processos[mais_curto].tempo_chegada;
        tempo_decorrido += processos[mais_curto].tempo_execucao;
        concluido[mais_curto] = true;
        tempo_total_espera += processos[mais_curto].tempo_espera;
    }

    cout << "SJF - Tempo médio de espera: " << (float)tempo_total_espera / n << " unidades\n";
}

// Função para calcular o tempo médio de espera para Prioridade (não preemptivo)
void calcular_prioridade(vector<Processo> &processos) {
    int n = processos.size();
    int tempo_total_espera = 0, tempo_decorrido = 0;
    vector<bool> concluido(n, false);

    for (int count_concluido = 0; count_concluido < n; count_concluido++) {
        int maior_prioridade = -1;

        for (int i = 0; i < n; i++) {
            if (!concluido[i] && processos[i].tempo_chegada <= tempo_decorrido) {
                if (maior_prioridade == -1 || processos[i].prioridade < processos[maior_prioridade].prioridade) {
                    maior_prioridade = i;
                }
            }
        }

        if (maior_prioridade == -1) {
            tempo_decorrido++;
            continue;
        }

        processos[maior_prioridade].tempo_espera = tempo_decorrido - processos[maior_prioridade].tempo_chegada;
        tempo_decorrido += processos[maior_prioridade].tempo_execucao;
        concluido[maior_prioridade] = true;
        tempo_total_espera += processos[maior_prioridade].tempo_espera;
    }

    cout << "Prioridade - Tempo médio de espera: " << (float)tempo_total_espera / n << " unidades\n";
}

// Função para calcular o tempo médio de espera para RR
void calcular_rr(vector<Processo> &processos, int quantum) {
    int n = processos.size();
    int tempo_total_espera = 0, tempo_decorrido = 0;
    vector<int> tempo_restante(n);

    for (int i = 0; i < n; i++) {
        tempo_restante[i] = processos[i].tempo_execucao;
    }

    while (true) {
        bool concluido = true;

        for (int i = 0; i < n; i++) {
            if (tempo_restante[i] > 0) {
                concluido = false;

                if (tempo_restante[i] > quantum) {
                    tempo_decorrido += quantum;
                    tempo_restante[i] -= quantum;
                } else {
                    tempo_decorrido += tempo_restante[i];
                    processos[i].tempo_espera = tempo_decorrido - processos[i].tempo_execucao - processos[i].tempo_chegada;
                    tempo_total_espera += processos[i].tempo_espera;
                    tempo_restante[i] = 0;
                }
            }
        }

        if (concluido) break;
    }

    cout << "RR - Tempo médio de espera: " << (float)tempo_total_espera / n << " unidades\n";
}

void exibir_diagrama_gantt(const vector<Processo> &processos) {
    cout << "\nDiagrama de Gantt:\n";

    // Linha superior com os processos
    cout << " ";
    for (const auto &p : processos) {
        for (int i = 0; i < p.tempo_execucao; i++) cout << "-";
        cout << " ";
    }
    cout << "\n|";
    for (const auto &p : processos) {
        int espaço = p.tempo_execucao / 2;
        for (int i = 0; i < espaço; i++) cout << " ";
        cout << "P" << p.id;
        for (int i = 0; i < espaço; i++) cout << " ";
        cout << "|";
    }
    cout << "\n ";
    for (const auto &p : processos) {
        for (int i = 0; i < p.tempo_execucao; i++) cout << "-";
        cout << " ";
    }
    cout << "\n";

    // Linha inferior com os tempos
    int tempo_atual = 0;
    cout << "0";
    for (const auto &p : processos) {
        tempo_atual += p.tempo_execucao;
        cout << setw(p.tempo_execucao + 1) << tempo_atual;
    }
    cout << "\n";
}

void salvar_dados_gantt(const string &arquivo, const vector<Processo> &processos) {
    ofstream saida(arquivo);
    if (!saida.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita!\n";
        return;
    }

    // Escreve os dados no formato: id,tempo_inicio,tempo_duracao
    for (const auto &p : processos) {
        saida << p.id << "," << p.tempo_chegada << "," << p.tempo_execucao << "\n";
    }
    saida.close();
    cout << "Dados salvos no arquivo " << arquivo << " com sucesso!\n";
}

int main() {
    vector<Processo> processos = {
        {1, 6, 0, 3},
        {2, 8, 1, 1},
        {3, 7, 2, 2},
        {4, 3, 3, 4},
        {5, 2, 4, 5}
    };

    vector<Processo> copia_processos;

    // FCFS
    copia_processos = processos;
    calcular_fcfs(copia_processos);
    //exibir_diagrama_gantt(copia_processos);
    salvar_dados_gantt("fcfs.csv", processos);

    // SJF
    copia_processos = processos;
    calcular_sjf(copia_processos);
    //exibir_diagrama_gantt(copia_processos);
    salvar_dados_gantt("sjf.csv", processos);
    
    // Prioridade
    copia_processos = processos;
    calcular_prioridade(copia_processos);
    //exibir_diagrama_gantt(copia_processos);
    salvar_dados_gantt("pri.csv", processos);

    // RR
    int quantum = 3;
    copia_processos = processos;
    calcular_rr(copia_processos, quantum);
    //exibir_diagrama_gantt(copia_processos);
    salvar_dados_gantt("rr.csv", processos);

    return 0;
}
