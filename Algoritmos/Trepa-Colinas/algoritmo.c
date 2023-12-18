#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo.h"
#include "utils.h"
#include "funcao.h"
#define PROB 0.01 // probabilidade fixa do algoritmo do trepa-colinas probabilistico

#define TMAX 100
#define TMIN 5

// Trepa colinas first-choice
// Parâmetros de entrada: Solucao, sol, Matriz de adjacencias, mat, Número de vértices, vert, Número de iterações, num_iter
// Parâmetros de saída: Custo da melhor solução encontrada
int trepa_colinas1(int sol[], int *mat, int vert, int num_iter)
{

    int *nova_sol, custo, custo_viz;

    // Aloca espaço em memória para guardar a nova solução
    nova_sol = malloc(sizeof(int) * vert);
    // Caso não consiga fazer a alocação, envia aviso e termina o programa
    if (nova_sol == NULL)
    {
        printf("Erro da alocacao de memoria\n");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);

    for (int i = 0; i < num_iter; i++)
    {
        // Gera solucao vizinha
        // Metodo 1
        gera_vizinho(sol, nova_sol, vert);
        custo_viz = calcula_fit(nova_sol, mat, vert);

        // alterar se for para aceitar custos inferiores ou iguais
        // Fica com a solução vizinha se o custo diminuir (problema de minimização) em relação à solução atual
        if (custo_viz < custo)
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
    }

    // Liberta a memória usada para guardar a nova solução
    free(nova_sol);
    // Devolve o custo da melhor solução encontrada
    return custo;
}

// com vizinhanca 2
int trepa_colinas2(int sol[], int *mat, int vert, int num_iter)
{

    int *nova_sol, custo, custo_viz;

    nova_sol = malloc(sizeof(int) * vert);

    if (nova_sol == NULL)
    {
        printf("Erro da alocacao de memoria\n");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);

    for (int i = 0; i < num_iter; i++)
    {
        // Gera solucao vizinha
        // Metodo 2
        gera_vizinho2(sol, nova_sol, vert);

        custo_viz = calcula_fit(nova_sol, mat, vert);

        // No futuro posso alterar para <=   (TABELA 2)
        if (custo_viz < custo)
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
    }

    free(nova_sol);
    return custo;
}
// Trepa colinas first-choice
// Parâmetros de entrada: Solucao, sol, Matriz de adjacencias, mat, Número de vértices, vert, Número de iterações, num_iter
// Parâmetros de saída: Custo da melhor solução encontrada
int trepa_colinas_prob1(int sol[], int *mat, int vert, int num_iter)
{

    int *nova_sol, custo, custo_viz;

    // Aloca espaço em memória para guardar a nova solução
    nova_sol = malloc(sizeof(int) * vert);
    // Caso não consiga fazer a alocação, envia aviso e termina o programa
    if (nova_sol == NULL)
    {
        printf("Erro da alocacao de memoria\n");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);

    for (int i = 0; i < num_iter; i++)
    {
        // Gera solucao vizinha
        // Metodo 1
        gera_vizinho(sol, nova_sol, vert);

        // Avalia solução vizinha
        custo_viz = calcula_fit(nova_sol, mat, vert);

        // se for só para aceitar custos inferiores tirar igual
        if (custo_viz <= custo)
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
        else
        {
            // Fica com a solução vizinha, apesar de pior, se o valor aleatório gerado for abaixo da probabilidade definida
            if (rand_01() < PROB)
            {
                substitui(sol, nova_sol, vert);
                custo = custo_viz;
            }
        }
    }
    // Liberta a memória usada para guardar a nova solução
    free(nova_sol);
    // Devolve o custo da melhor solução encontrada
    return custo;
}

// com vizinhanca 2
int trepa_colinas_prob2(int sol[], int *mat, int vert, int num_iter)
{

    int *nova_sol, custo, custo_viz;

    nova_sol = malloc(sizeof(int) * vert);

    if (nova_sol == NULL)
    {
        printf("Erro da alocacao de memoria\n");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);

    for (int i = 0; i < num_iter; i++)
    {
        // Gera solucao vizinha
        // Metodo 2
        gera_vizinho2(sol, nova_sol, vert);

        custo_viz = calcula_fit(nova_sol, mat, vert);

        // se for só para aceitar custos inferiores tirar igual
        if (custo_viz <= custo)
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
        else
        {
            if (rand_01() < PROB)
            {
                substitui(sol, nova_sol, vert);
                custo = custo_viz;
            }
        }
    }

    free(nova_sol);
    return custo;
}

// Gera um vizinho à distância 1 (troca um vértice de cada grupo)
// Parâmetros de entrada: Solução actual, a, Solução vizinha, b, Número de vértices, n
void gera_vizinho(int a[], int b[], int n)
{

    int p1, p2;

    // Faz uma copia
    for (int i = 0; i < n; i++)
    {
        b[i] = a[i];
    }
    // Encontra aleatoriamente a posição de um vértice com valor 0
    do
    {
        p1 = random_l_h(0, n - 1);
    } while (b[p1] != 0);
    // Encontra aleatoriamente a posição de um vértice com valor 1
    do
    {
        p2 = random_l_h(0, n - 1);
    } while (b[p2] != 1);

    // Troca os valores dos vértices das posições encontradas
    b[p1] = 1;
    b[p2] = 0;
}

// Gera um vizinho à distância 2 (troca dois vértices de cada grupo)
// Parâmetros de entrada: Solução actual, a, Solução vizinha, b, Número de vértices, n
void gera_vizinho2(int a[], int b[], int n)
{
    int p1, p2, p3, p4;
    // Copia a solução atual para a solução vizinha
    for (int i = 0; i < n; i++)
    {
        b[i] = a[i];
    }
    // Encontra aleatoriamente a posição de um vértice com valor 0
    do
    {
        p1 = random_l_h(0, n - 1);
    } while (b[p1] != 0);
    // Encontra aleatoriamente a posição de um vértice com valor 1
    do
    {
        p2 = random_l_h(0, n - 1);
    } while (b[p2] != 1);
    // Troca os valores dos vértices das posições encontradas
    b[p1] = 1;
    b[p2] = 0;
    // Encontra aleatoriamente a posição de um vértice, que não seja igual a p2, com valor 0

    do
    {
        p3 = random_l_h(0, n - 1);
    } while (b[p3] != 0 || p3 == p2);
    // Encontra aleatoriamente a posição de um vértice, que não seja igual a p1, com valor 1
    do
    {
        p4 = random_l_h(0, n - 1);
    } while (b[p4] != 1 || p4 == p1);
    // Troca os valores dos vértices das posições encontradas
    b[p3] = 1;
    b[p4] = 0;
}
