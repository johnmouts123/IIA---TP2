#include <stdio.h>
#include <stdlib.h>
#include "funcao.h"
/*
A função verifica a validade de uma solução, somando os custos associados às conexões entre os vértices que fazem parte da solução. Se um vértice estiver na solução, mas não estiver conectado a nenhum outro, a função retorna 1000, indicando uma solução inválida. Caso contrário, retorna a metade do custo total, pois cada aresta é contada duas vezes.
*/
int calcula_fit(int a[], int *mat, int vert)
{
    int total = 0;
    // Array para verificar se o vertice pertence a solucao e se tem ligacao a outro vertice da solucao
    int *con = (int *)malloc(vert * sizeof(int));
    for (int i = 0; i < vert; i++)
    {
        con[i] = 0;
    }

    // Loop por toda a matriz para verificar se é valida
    for (int i = 0; i < vert; i++)
    {
        // Verifica se a linha pertence a solucao
        if (a[i] == 1)
        {
            for (int j = 0; j < vert; j++)
            {
                if (a[j] == 1 && *(mat + i * vert + j) != 0)
                {
                    con[i] = 1;
                    con[j] = 1;

                    // Soma o custo da aresta
                    total += *(mat + i * vert + j);
                }
            }
        }
    }

    for (int i = 0; i < vert; i++)
    {
        if (con[i] == 0 && a[i] == 1)
        {
            // Solucao invalida
            free(con);
            return 1000;
        }
    }

    free(con);
    return total / 2;
}
