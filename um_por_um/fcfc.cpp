#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id;              // ID do processo
    int arrivalTime;     // Tempo de chegada
    int burstTime;       // Tempo de execução
    int waitingTime;     // Tempo de espera
    int turnaroundTime;  // Tempo de retorno

    Process(int id, int arrival, int burst)
        : id(id), arrivalTime(arrival), burstTime(burst),
          waitingTime(0), turnaroundTime(0) {}
};

void calculateFCFS(std::vector<Process>& processes) {
    int currentTime = 0;

    for (auto& process : processes) {
        // Tempo de espera = tempo atual - tempo de chegada
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime;
        }
        process.waitingTime = currentTime - process.arrivalTime;
        
        // Tempo de retorno = tempo de espera + tempo de execução
        process.turnaroundTime = process.waitingTime + process.burstTime;

        // Avança o tempo atual
        currentTime += process.burstTime;
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

int main() {
    std::vector<Process> processes = {
        {1, 0, 5},
        {2, 1, 3},
        {3, 2, 8},
        {4, 3, 6}
    };

    // Ordena os processos pelo tempo de chegada
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    // Calcula os tempos de espera e retorno usando FCFS
    calculateFCFS(processes);

    // Exibe os resultados
    printResults(processes);

    return 0;
}
