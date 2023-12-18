#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

#define PR 0.7
#define PM 0.001
#define TSIZE 2

void tournament(pchrom pop, int popsize, pchrom parents)
{
    int x1, x2;

    for (int i = 0; i < popsize; i++)
    {
        x1 = random_l_h(0, popsize - 1);

        do
        {
            x2 = random_l_h(0, popsize - 1);
        } while (x1 == x2);

        if (pop[x1].fitness < pop[x2].fitness)
        {
            parents[i] = pop[x1];
        }
        else
        {
            parents[i] = pop[x2];
        }
    }
}

void genetic_operator(pchrom parents, int popsize, pchrom offspring, int vert)
{
    // Recombinacao
    // 1 ponto de corte
    crossover(parents, offspring, popsize, vert);
    // 2 pontos de corte
    // recombinacao_dois_pontos_corte(parents, offspring, popsize, vert);

    // Mutacao
    // Binaria
    mutation(offspring, popsize, vert);
    // Por troca
    // mutacao_por_troca(offspring, popsize, vert);
}

void crossover(pchrom parents, pchrom offspring, int popsize, int vert)
{
    int point;

    for (int i = 0; i < popsize; i += 2)
    {
        if (rand_01() < PR)
        {
            point = random_l_h(0, vert - 1);

            for (int j = 0; j < point; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i + 1].p[j];
            }
            for (int j = point; j < vert; j++)
            {
                offspring[i].p[j] = parents[i + 1].p[j];
                offspring[i + 1].p[j] = parents[i].p[j];
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i + 1] = parents[i + 1];
        }
    }
}

void recombinacao_dois_pontos_corte(pchrom parents, pchrom offspring, int popsize, int vert)
{
    int p1, p2;

    for (int i = 0; i < popsize; i += 2)
    {
        if (rand_01() < PR)
        {
            p1 = random_l_h(0, vert - 1);
            p2 = random_l_h(0, vert - 1);

            for (int j = 0; j < p1; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i + 1].p[j];
            }

            for (int j = p1; j < p2; j++)
            {
                offspring[i].p[j] = parents[i + 1].p[j];
                offspring[i + 1].p[j] = parents[i].p[j];
            }

            for (int j = p2; j < vert; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i + 1].p[j];
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i + 1] = parents[i + 1];
        }
    }
}

void mutation(pchrom offspring, int popsize, int vert)
{

    for (int i = 0; i < popsize; i++)
    {
        for (int j = 0; j < vert; j++)
        {
            if (rand_01() < PM)
            {
                offspring[i].p[j] = !(offspring[i].p[j]);
            }
        }
    }
}

void mutacao_por_troca(pchrom offspring, int popsize, int vert)
{
    int p1, p2, aux;

    for (int i = 0; i < popsize; i++)
    {
        if (rand_01() < PM)
        {
            do
            {
                p1 = random_l_h(0, vert - 1);
            } while (offspring[i].p[p1] == 1);

            do
            {
                p2 = random_l_h(0, vert - 1);
            } while (offspring[i].p[p2] == 0);

            aux = offspring[i].p[p1];
            offspring[i].p[p1] = offspring[i].p[p2];
            offspring[i].p[p2] = aux;
        }
    }
}