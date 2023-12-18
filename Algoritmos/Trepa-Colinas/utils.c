#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Inicia o gerador de numeros aleatorios
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

void escreve_sol(int *sol, int vert)
{

    printf("\nSubconjunto: ");
    for (int i = 0; i < vert; i++)
    {
        if (sol[i] == 1)
        {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}

// Gera um valor inteiro aleatório entre min e max
// Parâmetros de entrada: Valor inferior do intervalo, min, Valor superior do intervalo, max
// Parâmetros de saída: Valor aleatório entre min e max
int random_l_h(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Gera um valor inteiro aleatório entre 0 e 1
// Parâmetros de saída: Valor aleatório entre 0 e 1
float rand_01()
{
    return ((float)rand()) / RAND_MAX;
}

// copia vector b para a (tamanho n)
// Parâmetros de entrada: Solução que será substituída, a, Solução que irá substituir, b, Número de vertices, n
void substitui(int a[], int b[], int n)
{

    for (int i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
}