#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define GENERATIONS_TC  100
#define PROBGERAVIZ     0.8

void evaluate(pchrom pop, int* mat, int vert, int k, int popsize) {
    for (int i = 0; i < popsize; i++) 
    {
        // Metodos de avaliar solucao
            // Penalizacao cega
          pop[i].fitness = calcula_fit(pop[i].p, mat, vert, k, &pop[i].valido);
            // Penalizacao nao cega
        //pop[i].fitness = calcula_fit_penalizado(pop[i].p, mat, vert, k, &pop[i].valido);
            // Reparacao1
        //pop[i].fitness = calcula_fit_reparado1(pop[i].p, mat, vert, k, &pop[i].valido);
            // Reparacao2
        //pop[i].fitness = calcula_fit_reparado2(pop[i].p, mat, vert, k, &pop[i].valido);
    }   
}

int calcula_fit(int a[], int *mat, int vert, int k, int *v) {
    int total = 0, lig = 0;

    for (int i = 0; i < vert; i++) 
    {
        if (a[i] == 1) 
        {
            lig++;
        }
    }

    // Numero de vertices do subconjunto diferente de K
    if (lig != k) 
    {
        *v = 0;
        return 10000;
    }

    // Array de conexoes
    int con[vert];
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
                if(a[j] == 1 && *(mat+i*vert+j) != 0) 
                {
                    con[i] = 1;
                    con[j] = 1;

                    // Adiciona o custo
                    total += *(mat+i*vert+j);
                }
            }
        }   
    }

    for (int i = 0; i < vert; i++) 
    {
        if (con[i] == 0 && a[i] == 1) 
        {
            // Solucao invalida - Não existem as ligacões necessárias
            *v = 0;
            return 10000;
        }
    }

    *v = 1;
    return total / 2;
}

int calcula_fit_penalizado(int a[], int *mat, int vert, int k, int *v) {
    int total = 0, lig = 0;

    for (int i = 0; i < vert; i++) 
    {
        if (a[i] == 1) 
        {
            lig++;
        }
    }

    // Penalizar 500 + 100 por cada vertice a mais ou a menos
    if (lig != k) 
    {
        *v = 0;
        return 500 + abs(((k-lig)*100));
    }

    // Array de conexoes
    int con[vert];
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
                if(a[j] == 1 && *(mat+i*vert+j) != 0) 
                {
                    con[i] = 1;
                    con[j] = 1;

                    // Adiciona o custo
                    total += *(mat+i*vert+j);
                }
            }
        }   
    }

    for (int i = 0; i < vert; i++) 
    {
        if (con[i] == 0 && a[i] == 1) 
        {
            // Penalizar 500 se não existirem as ligacoes necessarias
            *v = 0;
            return total + 500;
        }
    }

    *v = 1;
    return total / 2;
}

int calcula_fit_reparado1(int a[], int *mat, int vert, int k, int *v) {
    int total = 0, lig = 0;
    int prep;

    for (int i = 0; i < vert; i++) 
    {
        if (a[i] == 1) 
        {
            lig++;
        }
    }

    // Reparacao 1 -> Ajusta o tamanho do subconjunto para ficar igual a K
    if (lig > k) 
    {   
        do {
            do {
                prep = random_l_h(0, vert-1);
            }while(a[prep] != 1);
            
            a[prep] = 0;
            lig--;
        }while(lig != k);
    }
    if (lig < k) 
    {
        do {
            do {
                prep = random_l_h(0, vert-1);
            }while(a[prep] != 0);
            
            a[prep] = 1;
            lig++;
        }while(lig != k);
    }

    // Array de conexoes
    int con[vert];
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
                if(a[j] == 1 && *(mat+i*vert+j) != 0) 
                {
                    con[i] = 1;
                    con[j] = 1;

                    // Adiciona o custo
                    total += *(mat+i*vert+j);
                }
            }
        }   
    }

    for (int i = 0; i < vert; i++) 
    {
        if (con[i] == 0 && a[i] == 1) 
        {
            // Solucao invalida
            *v = 0;
            return 10000;
        }
    }

    *v = 1;
    return total / 2;
}

int calcula_fit_reparado2(int a[], int *mat, int vert, int k, int *v) {
    int total = 0, lig = 0;
    int prep, ncon = 0;

    for (int i = 0; i < vert; i++) 
    {
        if (a[i] == 1) 
        {
            lig++;
        }
    }

    // Reparacao 1
    if (lig > k) 
    {
        do {
            do {
                prep = random_l_h(0, vert-1);
            }while(a[prep] != 1);
            
            a[prep] = 0;
            lig--;
        }while(lig != k);
    }
    if (lig < k) 
    {
        do {
            do {
                prep = random_l_h(0, vert-1);
            }while(a[prep] != 0);
            
            a[prep] = 1;
            lig++;
        }while(lig != k);
    }

    // Array de conexoes
    int con[vert];
    for (int i = 0; i < vert; i++) 
    {
        con[i] = 0;
    }

    for (int i = 0; i < vert; i++) 
    {
        if (a[i] == 1) 
        {
            for (int j = 0; j < vert; j++) 
            {
                if(a[j] == 1 && *(mat+i*vert+j) != 0) 
                {
                    con[i] = 1;
                    con[j] = 1;
                }
            }
        }
    }

    // Verifica se o num de conexoes criadas é menor que k (Assim sera impossivel)
    for (int i = 0; i < vert; i++) 
    {
        if (con[i] == 1) 
        {
            ncon++;
        }
    }
    if (ncon < k) 
    {
        *v = 0;
        return 10000;
    }  

    // Reparacao nova -> Faz substituição dos vertices sem ligacao por vertices que tenham alguma ligacao com o conjunto mas não fazem parte dele
    for (int i = 0; i < vert; i++) 
    {
        if (con[i] == 0 && a[i] == 1) 
        {
            // Solucao invalida
            do {
                prep = random_l_h(0, vert-1);
            }while(con[prep] == 1 && a[prep] == 0);

            a[i] = 0;
            a[prep] = 1;
        }
    }

    // Loop por toda a matriz para verificar se é valida
    for (int i = 0; i < vert; i++) 
    {
        // Verifica se a linha pertence a solucao
        if (a[i] == 1) 
        {
            for (int j = 0; j < vert; j++) 
            {
                if(a[j] == 1 && *(mat+i*vert+j) != 0) 
                {             
                    // Adiciona o custo
                    total += *(mat+i*vert+j);
                }
            }
        }   
    }

    *v = 1;
    return total / 2;
}



// Funcoes trepa colinas (Hibrido)

void trepa_colinas(pchrom pop, int popsize, int *mat, int vert, int k) {
    chrom vizinho;

    for (int i = 0; i < popsize; i++) 
    {
        for (int j = 0; j < GENERATIONS_TC; j++) 
        {
            gera_vizinho(pop[i].p, vizinho.p, vert);
            vizinho.fitness = calcula_fit(vizinho.p, mat, vert, k, &vizinho.valido);

            if (vizinho.fitness <= pop[i].fitness)
            {
                pop[i] = vizinho;
            }
        }
    }
}

void gera_vizinho(int a[], int b[], int n) {

    int p1, p2;

    // Faz uma copia
    for (int i = 0; i < n; i++) 
    {
        b[i] = a[i];
    }

    do {
        p1 = random_l_h(0, n-1);
    } while(b[p1] != 0);

    do {
        p2 = random_l_h(0, n-1);
    } while(b[p2] != 1);

    // Troca
    b[p1] = 1;
    b[p2] = 0;
}
