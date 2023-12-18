#define _CRT_SECURE_NO_WARNINGS 1
#define POPSIZE 100
#define GENERATIONS 2500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"
#include "funcao.h"

#define DEFAULT_RUNS 100

int main(int argc, char* argv[]) {

    char nome_fich[100];
    int runs, k, vert, ares, gen_atual, inv;
    int *grafo;
    float mbf = 0.0;

    pchrom pop = NULL, parents = NULL;
    chrom best_run, best_ever;  

    if (argc == 3) 
    {
        runs = atoi(argv[2]);
        strcpy(nome_fich, argv[1]);
    }
    else if (argc == 2) 
    {
        runs = DEFAULT_RUNS;
        strcpy(nome_fich, argv[1]);
    } 
    else 
    {
        printf("Sintaxe invalida: ./test <ficheiro> <runs>");
        return 0;
    }
    
    if (runs <= 0) 
    {
        return 0;
    }

    init_rand();
    grafo = init_dados(nome_fich, &k, &vert, &ares);

    // Iniciar dados
    for (int i = 0; i < runs; i++) 
    {
        printf("Repeticao %d:\n", i+1);

        // Gera populacao inicial
        pop = init_pop(vert, k);

        // Avalia populacao inicial
        evaluate(pop, grafo, vert, k, POPSIZE);

        // Trepa i)
        trepa_colinas(pop, POPSIZE, grafo, vert, k);

        best_run = pop[0];
        best_run = get_best(pop, POPSIZE, best_run);

        parents = malloc(sizeof(chrom)*POPSIZE);
        if (parents == NULL) 
        {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }

        gen_atual = 1;
        // Clico de otimizacao
        while (gen_atual <= GENERATIONS) 
        {
            // Encontrar os progenitores
                // Torneio binario
            tournament(pop, POPSIZE, parents);
                
            
            // Operadores genericos
            genetic_operator(parents, POPSIZE, pop, vert);

            // Avalia nova populacao
            evaluate(pop, grafo, vert, k, POPSIZE);

            // Atualiza nova solucao
            best_run = get_best(pop, POPSIZE, best_run);
            gen_atual++;
        }


        // Contagem de solucoes invalidas
        inv = 0;
        for (int i = 0; i < POPSIZE; i++) 
        {
            if (pop[i].valido == 0) 
            {
                inv++;
            }
        }

        // Escreve resultados
        write_best(best_run, vert);
        printf("\nPercentagem Invalidos %f\n", 100*(float)inv/POPSIZE);

        mbf += best_run.fitness;
        if (i == 0 || best_run.fitness < best_ever.fitness) 
        {
            best_ever = best_run;
        }

        free(parents);
        free(pop);
    }

    // Resultados finais
    printf("\n\nMBF: %f\n", mbf/runs);
    printf("\nMelhor solucao encontrada");
    write_best(best_ever, vert);

    return 0;
}