#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "algoritmo.h"

#define DEFAULT_RUNS 100
#define NUM_ITER 1000

int main(int argc, char *argv[])
{
    char nome_fich[100];
    int runs, k, vert, ares, custo, best_custo = 1000;
    int *grafo, *sol, *best;
    float mbf = 0.0;
    int op = 0;
    // Lê os argumentos de entrada
    if (argc == 3)
    {
        runs = atoi(argv[2]);
        strcpy(nome_fich, argv[1]);

    } // Se o número de execuções do processo não for colocado nos argumentos de entrada, define-o com um valor por defeito
    else if (argc == 2)
    {
        runs = DEFAULT_RUNS;
        strcpy(nome_fich, argv[1]);
    }
    else // Se o nome do ficheiro e o número de execuções do processo não forem colocados nos argumentos de entrada, pede-os ao utilizador
    {
        runs = DEFAULT_RUNS;
        printf("Nome do Ficheiro: ");
        gets(nome_fich);
    }

    if (runs <= 0)
    {
        return 0;
    }

    init_rand();
    grafo = init_dados(nome_fich, &k, &vert, &ares);

    sol = malloc(sizeof(int) * vert);
    best = malloc(sizeof(int) * vert);

    if (sol == NULL || best == NULL)
    {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    do
    {
        printf("\n\n--------------------------------------------------------------\n\n");
        printf("         1- Usar gera_vizinho1 \n");
        printf("         2- Usar gera_vizinho2 \n");
        printf("         3- Voltar \n\n");
        printf("--------------------------------------------------------------\n\n");
        printf(">>Opcao: ");
        scanf("%d", &op);
    } while (op < 1 || op > 2);

    int metodo_opcao;

    do
    {
        printf("\n\n--------------------------------------------------------------\n\n");
        printf("         1- Usar metodo normal\n");
        printf("         2- Usar metodo probabilistico\n");
        printf("         3- Voltar \n\n");
        printf("--------------------------------------------------------------\n\n");
        printf(">>Opcao: ");
        scanf("%d", &metodo_opcao);
    } while (metodo_opcao < 1 || metodo_opcao > 2);

    for (int i = 0; i < runs; i++)
    {

        gera_sol_inicial(sol, vert, k);
        escreve_sol(sol, vert);

        // Trepa colinas
        if (op == 1)
        {
            if (metodo_opcao == 1)
            {
                custo = trepa_colinas1(sol, grafo, vert, NUM_ITER);
            }
            else if (metodo_opcao == 2)
            {
                custo = trepa_colinas_prob1(sol, grafo, vert, NUM_ITER);
            }
            else
            {
                printf("Opcao de metodo invalida.\n");
                return 1;
            }
        }
        else if (op == 2)
        {
            if (metodo_opcao == 1)
            {
                custo = trepa_colinas2(sol, grafo, vert, NUM_ITER);
            }
            else if (metodo_opcao == 2)
            {
                custo = trepa_colinas_prob2(sol, grafo, vert, NUM_ITER);
            }
            else
            {
                printf("Opcao de metodo invalida.\n");
                return 1;
            }
        }
        else
        {
            printf("Opcao de vizinhanca invalida.\n");
            return 1;
        }

        // Escreve os resultados da repeticao i
        printf("\nRepeticao %d:", i);
        escreve_sol(sol, vert);
        printf("Custo final: %2d\n", custo);

        mbf += custo;

        if (best_custo > custo)
        {
            best_custo = custo;
            substitui(best, sol, vert);
        }
    }

    printf("\n\n MBF: %f\n", mbf / runs);
    printf("\nMelhor solucao encontrada");
    escreve_sol(best, vert);
    printf("Custo final: %2d\n", best_custo);

    free(grafo);
    free(sol);
    free(best);
    return 0;
}
