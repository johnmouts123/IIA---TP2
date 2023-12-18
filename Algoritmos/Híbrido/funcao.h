void evaluate(pchrom pop, int* mat, int vert, int k, int popsize);

int calcula_fit(int a[], int *mat, int vert, int k, int *v);
int calcula_fit_penalizado(int a[], int *mat, int vert, int k, int *v);
int calcula_fit_reparado1(int a[], int *mat, int vert, int k, int *v);
int calcula_fit_reparado2(int a[], int *mat, int vert, int k, int *v);

void trepa_colinas(pchrom pop, int popsize, int *mat, int vert, int k);
void gera_vizinho(int a[], int b[], int n);


