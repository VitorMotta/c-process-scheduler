#include <stdio.h>
#include <stdlib.h>

#include "../include/processo.h"
#include "auxiliar.c"

#define TEMPO_MAXIMO_CPU 10 /* Tempo maximo de CPU */
#define TEMPO_MINIMO_CPU 5 /* Tempo minimo de CPU */
#define TEMPO_MAXIMO_INICIO 4 /* Tempo maximo de inicio */

Processo *aloca_processo(void) {
    Processo *processo = NULL;
    controla_erro_alocacao(processo = (Processo *) malloc(sizeof(Processo)));
    return processo;
}

Processo *aloca_processos(int num_processos) {
    Processo *processos = NULL;
    controla_erro_alocacao(processos = (Processo *) calloc(num_processos, sizeof(Processo)));
    return processos;
}

OperacaoES *aloca_operacoes_es(int num_operacoes_es) {
    OperacaoES *operacoes_es = NULL;
    controla_erro_alocacao(operacoes_es = (OperacaoES *) calloc(num_operacoes_es, sizeof(OperacaoES)));
    return operacoes_es;
}

int seleciona_tempo_es(TipoES tipo_es) {
    switch (tipo_es) {
        case DISCO:
            return TEMPO_DISCO;
        case FITA:
            return TEMPO_FITA;
        case IMPRESSORA:
            return TEMPO_IMPRESSORA;
        default:
            return 0;
    }
}

const char *seleciona_tipo_es(TipoES tipo_es) {
    switch (tipo_es) {
        case DISCO:
            return "Disco";
        case FITA:
            return "Fita";
        case IMPRESSORA:
            return "Impressora";
        default:
            return "Desconhecido";
    }
}

const char *seleciona_status_processo(StatusProcesso status_processo) {
    switch (status_processo) {
        case PRONTO:
            return "PRONTO";
        case EXECUTANDO:
            return "EXECUTANDO";
        case ENTRADA_SAIDA:
            return "ENTRADA E/OU SAIDA";
        default:
            return "DESCONHECIDO";
    }
}

Processo *cria_processo(int pid) {
    Processo *processo = aloca_processo();
    int i = 0;

    processo->pid = pid;
    processo->tempo_inicio = rand() % (TEMPO_MAXIMO_INICIO + 1);
    processo->tempo_cpu = rand() % (TEMPO_MAXIMO_CPU - TEMPO_MINIMO_CPU + 1) + TEMPO_MINIMO_CPU;
    processo->tempo_cpu_restante = processo->tempo_cpu;
    processo->tempo_quantum_restante = 0;
    processo->tempo_cpu_atual = 0;
    processo->status_processo = PRONTO;

    processo->num_operacoes_es = rand() % QUANTIDADE_TIPOS_ES;
    if (processo->num_operacoes_es == 0)
        return processo;

    processo->operacao_es_atual = 0;
    processo->operacoes_es = aloca_operacoes_es(processo->num_operacoes_es);

    for (i = 0; i < processo->num_operacoes_es; i++) {
        processo->operacoes_es[i].tipo_es = rand() % QUANTIDADE_TIPOS_ES;
        processo->operacoes_es[i].duracao_es = seleciona_tempo_es(processo->operacoes_es[i].tipo_es);
        processo->operacoes_es[i].tempo_inicio = rand() % QUANTIDADE_TIPOS_ES + 1;
        processo->operacoes_es[i].tempo_restante = processo->operacoes_es[i].duracao_es;
    }

    quicksort(processo->operacoes_es, 0, processo->num_operacoes_es - 1);

    return processo;
}

Processo *inicializa_processos(int qtd_processos) {
    Processo *processos = aloca_processos(qtd_processos);
    int i = 0;

    for (i = 0; i < qtd_processos; i++)
        processos[i] = *cria_processo(i);

    return processos;
}

void executa_processo(Processo *processo) {
    printf("O processo P%d executou por 1 u.t.\n", processo->pid);
    processo->tempo_cpu_restante -= 1;
    processo->tempo_cpu_atual += 1;
    processo->tempo_quantum_restante += 1;
    processo->status_processo = EXECUTANDO;
}

int processo_finalizado(Processo *processo) {
    if (processo->tempo_cpu_restante == 0) {
        printf("O processo P%d finalizou sua execucao.\n", processo->pid);
        return 1;
    }
    return 0;
}

int tempo_inicio_es(Processo *processo) {
    if (processo->operacoes_es != NULL) {
        if (processo->tempo_cpu_atual == processo->operacoes_es[processo->operacao_es_atual].tempo_inicio)
            return 1;
        else
            return 0;
    }
    return 0;
}

void executa_es(Processo *processo) {
    if (processo->status_processo == EXECUTANDO)
        processo->status_processo = ENTRADA_SAIDA;
    else {
        processo->operacoes_es[processo->operacao_es_atual].tempo_restante -= 1;
        printf("O processo P%d executou 1 u.t. da sua E/S de %s, faltam %d u.t.\n",
            processo->pid,
            seleciona_tipo_es(processo->operacoes_es[processo->operacao_es_atual].tipo_es),
            processo->operacoes_es[processo->operacao_es_atual].tempo_restante);
    }
}

int es_finalizada(Processo *processo) {
    if (processo->operacoes_es[processo->operacao_es_atual].tempo_restante == 0) {
        printf("O processo P%d finalizou sua E/S de %s,", processo->pid,
            seleciona_tipo_es(processo->operacoes_es[processo->operacao_es_atual].tipo_es));
        processo->tempo_quantum_restante = 0;
        processo->operacao_es_atual++;
        return 1;
    }
    return 0;
}

int tempo_quantum_completo(Processo *processo, int quantum) {
    if (processo->tempo_quantum_restante == quantum) {
        processo->tempo_quantum_restante = 0;
        return 1;
    }
    return 0;
}