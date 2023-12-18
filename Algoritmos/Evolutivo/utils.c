#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"

void init_rand()
{
    srand((unsigned)time(NULL));
}

int *init_dados(char *nome, int *k, int *vert, int *ares)
{
    FILE *f;
    int *p, *q;
    int v1, v2, c;

    f = fopen(nome, "r");

    if (f == NULL)
    {
        printf("Erro no acesso ao ficheiro de dados\n");
        exit(1);
    }

    // Numero K
    fscanf(f, "k %d", k);
    // Numero de arestas e vertices
    fscanf(f, "\np edge %d %d", vert, ares);

    p = malloc(sizeof(int) * (*vert) * (*vert));

    if (p == NULL)
    {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    // Inicializar toda a array a 0
    for (int i = 0; i < *vert; i++)
    {
        for (int j = 0; j < *vert; j++)
        {
            p[i * (*vert) + j] = 0;
        }
    }

    // Coloca as informações das arestas e os seus respetivos custos no array
    while (fscanf(f, "\ne %d %d %d", &v1, &v2, &c) == 3)
    {
        p[(v1 - 1) * (*vert) + (v2 - 1)] = c;
        p[(v2 - 1) * (*vert) + (v1 - 1)] = c;
    }

    fclose(f);
    return p;
}

pchrom init_pop(int vert, int k)
{
    pchrom indiv;

    indiv = malloc(sizeof(chrom) * 100); // Popsize

    if (indiv == NULL)
    {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    for (int i = 0; i < 100; i++)
    {
        gera_sol_inicial(indiv[i].p, vert, k);
    }

    return indiv;
}

void gera_sol_inicial(int *sol, int vert, int k)
{
    int x;

    for (int i = 0; i < vert; i++)
    {
        sol[i] = 0;
    }

    for (int i = 0; i < k; i++)
    {
        do
        {
            x = random_l_h(0, vert - 1);
        } while (sol[x] != 0);

        sol[x] = 1;
    }
}

chrom get_best(pchrom pop, int popsize, chrom best)
{
    for (int i = 0; i < popsize; i++)
    {
        if (best.fitness > pop[i].fitness)
        {
            best = pop[i];
        }
    }
    return best;
}

void write_best(chrom x, int vert)
{
    printf("\nBest individual: %d\n", x.fitness);

    for (int i = 0; i < vert; i++)
    {
        printf("%d", x.p[i]);
    }
    printf("\n");
}

int random_l_h(int min, int max)
{
    return min + rand() % (max - min + 1);
}

float rand_01()
{
    return ((float)rand()) / RAND_MAX;
}

int flip()
{
    if ((((float)rand()) / RAND_MAX) < 0.5)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}