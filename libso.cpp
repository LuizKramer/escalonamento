#include "libso.h"

float media(int n, Processo processos[]) {
    float somaEspera = 0;
    for(int i = 0; i < n; i++) {
        somaEspera += processos[i].tempoEspera;
    }
    return somaEspera / n;
}
