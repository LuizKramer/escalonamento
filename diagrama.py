import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import csv

# Função para ler dados do arquivo
def ler_arquivo(arquivo):
    processos = {}
    with open(arquivo, "r") as f:
        leitor = csv.reader(f)
        for linha in leitor:
            id_processo = linha[0]
            tempo_inicio = int(linha[1])
            tempo_duracao = int(linha[2])
            if id_processo not in processos:
                processos[id_processo] = []
            processos[id_processo].append((tempo_inicio, tempo_duracao))
    return processos

# Função para gerar o diagrama de Gantt
def gerar_diagrama(processos, titulo="Diagrama de Gantt"):
    fig, ax = plt.subplots(figsize=(10, 5))
    y_positions = range(len(processos), 0, -1)

    for i, (id_processo, intervalos) in enumerate(processos.items()):
        y = y_positions[i]
        for inicio, duracao in intervalos:
            ax.broken_barh([(inicio, duracao)], (y - 0.4, 0.8), facecolors="C" + str(i), edgecolor="black")

    # Configuração dos eixos
    ax.set_yticks(y_positions)
    ax.set_yticklabels(processos.keys())
    ax.set_xticks(range(0, 21))  # Ajuste o intervalo conforme necessário
    ax.set_xlabel("Tempo")
    ax.set_ylabel("Processos")
    ax.set_title(titulo)
    ax.grid(True, linestyle="--", alpha=0.5)

    plt.tight_layout()
    plt.show()

# Leitura do arquivo e geração do diagrama
arquivo = "fcfs.csv"  # Altere para o arquivo desejado (fcfs.csv, sjf.csv, etc.)
processos = ler_arquivo(arquivo)
gerar_diagrama(processos, titulo="Diagrama de Gantt - FCFS")
