#include <stdio.h>
#include <stdlib.h>

#define ARQUIVO_HISTORICO "historico.txt"

typedef struct {
    int id;
    int pontos_time1;
    int pontos_time2;
} Partida;

void limpar_buffer_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int registrar_partida(const Partida *partida) {
    FILE *arquivo = fopen(ARQUIVO_HISTORICO, "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o historico para gravacao");
        return 0;
    }

    fprintf(arquivo, "%d %d %d\n",
            partida->id,
            partida->pontos_time1,
            partida->pontos_time2);

    fclose(arquivo);
    return 1;
}

void listar_historico(void) {
    FILE *arquivo = fopen(ARQUIVO_HISTORICO, "r");
    if (arquivo == NULL) {
        printf("Historico vazio.\n");
        return;
    }

    Partida partida;
    int contador = 0;
    int retorno;

    while (1) {
        retorno = fscanf(arquivo, "%d %d %d",
                         &partida.id,
                         &partida.pontos_time1,
                         &partida.pontos_time2);

        if (retorno == EOF) {
            break;
        }

        if (retorno != 3) {
            fprintf(stderr, "Dado malformado no historico. Registro ignorado.\n");

            int c;
            while ((c = fgetc(arquivo)) != '\n' && c != EOF) {
            }

            continue;
        }

        contador++;
        printf("Partida %d: %d x %d\n",
               partida.id,
               partida.pontos_time1,
               partida.pontos_time2);
    }

    if (ferror(arquivo)) {
        perror("Erro ao ler o historico");
    } else if (contador == 0) {
        printf("Historico vazio.\n");
    } else {
        printf("Fim do historico. %d registros lidos.\n", contador);
    }

    fclose(arquivo);
}

int main(void) {
    Partida partidas[] = {
        {1, 2, 1},
        {2, 3, 3},
        {3, 4, 0},
        {4, 1, 2}
    };

    int qtd = sizeof(partidas) / sizeof(partidas[0]);

    for (int i = 0; i < qtd; i++) {
        registrar_partida(&partidas[i]);
    }

    printf("Historico atual:\n");
    listar_historico();

    return 0;
}
