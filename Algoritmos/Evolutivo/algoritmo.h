#define MAX_SUBCONJUNTO 100

// Solucao
typedef struct individual chrom, *pchrom;
struct individual
{
    int p[MAX_SUBCONJUNTO];
    int fitness;
    int valido;
};

// Funcoes
void tournament(pchrom pop, int popsize, pchrom parents);
void genetic_operator(pchrom parents, int popsize, pchrom offspring, int vert);

void crossover(pchrom parents, pchrom offspring, int popsize, int vert);
void recombinacao_dois_pontos_corte(pchrom parents, pchrom offspring, int popsize, int vert);

void mutation(pchrom offspring, int popsize, int vert);
void mutacao_por_troca(pchrom offspring, int popsize, int vert);
