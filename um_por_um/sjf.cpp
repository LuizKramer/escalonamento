#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // Para formatar saída

struct Process {
    int id;              // ID do processo
    int arrivalTime;     // Tempo de chegada
    int burstTime;       // Tempo de execução
    int waitingTime;     // Tempo de espera
    int turnaroundTime;  // Tempo de retorno
    int startTime;       // Tempo de início (para o Gantt Chart)

    Process(int id, int arrival, int burst)
        : id(id), arrivalTime(arrival), burstTime(burst),
          waitingTime(0), turnaroundTime(0), startTime(0) {}
};

void calculateSJF(std::vector<Process>& processes) {
    int currentTime = 0;
    std::vector<bool> completed(processes.size(), false); // Para rastrear processos concluídos

    for (size_t i = 0; i < processes.size(); ++i) {
        // Encontra o próximo processo com menor burstTime que chegou
        int shortestIndex = -1;
        for (size_t j = 0; j < processes.size(); ++j) {
            if (!completed[j] && processes[j].arrivalTime <= currentTime) {
                if (shortestIndex == -1 || processes[j].burstTime < processes[shortestIndex].burstTime) {
                    shortestIndex = j;
                }
            }
        }

        // Se nenhum processo pode ser executado, avance no tempo
        if (shortestIndex == -1) {
            currentTime++;
            i--; // Reavaliar no próximo loop
            continue;
        }

        // Atualiza os tempos do processo selecionado
        processes[shortestIndex].startTime = currentTime;
        processes[shortestIndex].waitingTime = currentTime - processes[shortestIndex].arrivalTime;
        processes[shortestIndex].turnaroundTime = processes[shortestIndex].waitingTime + processes[shortestIndex].burstTime;

        // Avança o tempo e marca o processo como concluído
        currentTime += processes[shortestIndex].burstTime;
        completed[shortestIndex] = true;
    }
}

void printResults(const std::vector<Process>& processes) {
    std::cout << "ID\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (const auto& process : processes) {
        std::cout << process.id << "\t" << process.arrivalTime << "\t"
                  << process.burstTime << "\t" << process.waitingTime << "\t"
                  << process.turnaroundTime << "\n";
    }
}

void printGanttChart(const std::vector<Process>& processes) {
    std::cout << "\nDiagrama de Gantt:\n";

    // Ordena os processos por tempo de início para o Gantt Chart
    std::vector<Process> ganttProcesses = processes;
    std::sort(ganttProcesses.begin(), ganttProcesses.end(), [](const Process& a, const Process& b) {
        return a.startTime < b.startTime;
    });

    // Linha superior com os IDs dos processos
    std::cout << " ";
    for (const auto& process : ganttProcesses) {
        std::cout << std::setw(3) << "P" << process.id << " ";
    }
    std::cout << "\n";

    // Linha inferior com os tempos
    std::cout << ganttProcesses[0].startTime; // O tempo inicial do primeiro processo
    for (const auto& process : ganttProcesses) {
        std::cout << std::setw(4) << process.startTime + process.burstTime;
    }
    std::cout << "\n";
}

int main() {
    std::vector<Process> processes = {
        {1, 0, 6},
        {2, 1, 8},
        {3, 2, 7},
        {4, 3, 3}
    };

    // Calcula os tempos de espera e retorno usando SJF
    calculateSJF(processes);

    // Exibe os resultados
    printResults(processes);

    return 0;
}
