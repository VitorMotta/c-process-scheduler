#include <stdio.h>

#include "../include/auxiliar.h"

void quicksort(OperacaoES *operacoes_es, int inicio, int fim) {
    int pos_pivo = 0;

    if (fim > inicio) {
        pos_pivo = particiona(operacoes_es, inicio, fim);
        quicksort(operacoes_es, inicio, pos_pivo - 1);
        quicksort(operacoes_es, pos_pivo + 1, fim);
    }
}

int particiona(OperacaoES *operacoes_es, int inicio, int fim) {
    int pos_pivo = 0;
    OperacaoES pivo;
    int i = inicio, j = fim;

    pos_pivo = rand() % (fim + 1 - inicio) + inicio;
    pivo = operacoes_es[pos_pivo];

    operacoes_es[pos_pivo] = operacoes_es[inicio];
    operacoes_es[inicio] = pivo;

    while (i < j) {
        while (i < fim && operacoes_es[i].tempo_inicio <= pivo.tempo_inicio) i++;
        while (j > inicio && operacoes_es[j].tempo_inicio > pivo.tempo_inicio) j--;
        if (i < j) troca(&operacoes_es[i], &operacoes_es[j]);
    }

    operacoes_es[inicio] = operacoes_es[j];
    operacoes_es[j] = pivo;
    return j;
}

void troca(OperacaoES *a, OperacaoES *b) {
    OperacaoES temp = *b;
    *b = *a;
    *a = temp;
}

void controla_erro_alocacao(void *ponteiro) {
    if (!ponteiro) {
        printf("Erro de alocacao.\n");
        exit(1);
    }
}