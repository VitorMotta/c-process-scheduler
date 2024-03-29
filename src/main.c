#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "processo.c"
#include "fila.c"
#include "escalonador.c"

int main(void) {
    Processo *processos = inicializa_processos(MAXIMO_PROCESSOS);
    Fila fila_alta_prioridade, fila_baixa_prioridade, fila_disco, fila_fita, fila_impressora;

    srand(time(NULL));

    inicializa_fila(&fila_alta_prioridade);
    inicializa_fila(&fila_baixa_prioridade);
    inicializa_fila(&fila_disco);
    inicializa_fila(&fila_fita);
    inicializa_fila(&fila_impressora);

    escalonador(processos, &fila_alta_prioridade, &fila_baixa_prioridade, &fila_disco, &fila_fita, &fila_impressora);

    esvazia_fila(&fila_alta_prioridade);
    esvazia_fila(&fila_baixa_prioridade);
    esvazia_fila(&fila_disco);
    esvazia_fila(&fila_fita);
    esvazia_fila(&fila_impressora);

    return 0;
}