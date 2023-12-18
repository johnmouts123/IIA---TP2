
void init_rand();
int *init_dados(char *nome, int *k, int *vert, int *ares);

pchrom init_pop(int vert, int k);
void gera_sol_inicial(int *sol, int vert, int k);

chrom get_best(pchrom pop, int popsize, chrom best);
void write_best(chrom x, int vert);

int random_l_h(int min, int max);
float rand_01();
int flip();