#ifndef AUXILIAR_H
#define AUXILIAR_H

#include "processo.h"

/* Funcao para realizar a ordenacao rapida */
/* Recebe um vetor de operacoes de E/S, o inicio e o fim do vetor */
/* Nao retorna valores */
void quicksort(OperacaoES *operacoes_es, int inicio, int fim);

/* Funcao para particionar o vetor */
/* Recebe um vetor de operacoes de E/S, o inicio e o fim do vetor */
/* Retorna a posicao do pivo */
int particiona(OperacaoES *operacoes_es, int inicio, int fim);

/* Funcao para trocar dois elementos de posicao */
/* Recebe dois ponteiros para operacoes de E/S */
/* Nao retorna valores */
void troca(OperacaoES *a, OperacaoES *b);

/* Funcao para controle de erros de alocacao */
/* Recebe um ponteiro */
/* Nao retorna valores */
void controla_erro_alocacao(void *ponteiro);

#endif /* AUXILIAR_H */