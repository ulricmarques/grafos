/**
 *   TRABALHO DE GRAFOS - ENGENHARIA DE COMPUTAÇÃO - TARDE
 *
 *   Desenvolvido na IDE DEV-C++
 *
 *   EQUIPE:
 *       - Cláudia Mariana Costa Maia
 *       - Jorge Girão Limaverde Lima
 *	 - Thalia Nascimento de Sousa Freitas
 *       - Ulric Marques Ferreira
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <limits.h>

/* Vértices de grafos são representados por variáveis do tipo 'vertice',
para facilitar a identificação.*/ 
#define vertice int

/* Variáveis do tipo 'INF' representam o valor infinito, que será usado para indicar
que dois vértices não possuem ligação. Também será usado durante o algoritmo de Dijkstra,
para indicar que não é possível chegar a um vértice partindo da origem. */
#define INF INT_MAX

/* A estrutura 'grafo' representa um grafo. 
	 O campo 'adj' é um ponteiro para a matriz de adjacências do grafo. 
	 O campo 'V' contém o número de vértices e o campo 'A' contém o número de arcos do grafo. */
	struct grafo {
	   int V; 
	   int A; 
	   int **adj; 
	};
	
	/* Um 'Grafo' é um ponteiro para um grafo, ou seja, um 'Grafo' contém o endereço de um grafo. */
	typedef struct grafo *Grafo;



void limpaTela(){
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
		system("clear");
	#endif

	#if defined(_WIN32) || defined(_WIN64)
		system("cls");
	#endif
}

/* A função alocaMatriz() aloca uma matriz com linhas 1,2,...,l e colunas 1..c. 
Cada elemento da matriz recebe valor val. */
static int **alocaMatriz(int l, int c, int val) { 
   vertice i, j;
   int **m = malloc((l+1) * sizeof (int *));
   for (i = 1; i <= l; ++i) 
	  m[i] = malloc((c+1) * sizeof (int));
   for (i = 1; i <= l; ++i)
	  for (j = 1; j <= c; ++j)
		 m[i][j] = val;
   return m;
}

/* A função inicializaGrafo() constrói um grafo com vértices 1,2,...,V e nenhum arco. */
Grafo inicializaGrafo(int V) { 
   Grafo G = malloc(sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = alocaMatriz(V, V, INF);
   return G;
}

/* A função insereArco() insere um arco v-w com custo c no grafo G.
A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void insereArco(Grafo G, vertice v, vertice w, int c) { 
   if (G->adj[v][w] == INF) {
	  G->adj[v][w] = c; 
	  G->A++;
   }
}


/* A função mostraGrafo() imprime, para cada vértice v do grafo G,
em uma linha, todos os vértices adjacentes a v. Também imprime os custos de cada arco. */
void mostraGrafo(Grafo G) { 
	vertice v,w;
	printf("\n");
	for (v = 1; v <= G->V; ++v) {
		printf("%2d:", v);
		for (w = 1; w <= G->V; ++w)
			if (G->adj[v][w] != INF) 
				printf(" %2d", w);
		printf("\n");
	}
   
	printf("\n");
   
	for (v = 1; v <= G->V; ++v) {
		for (w = 1; w <= G->V; ++w){
			if (G->adj[v][w] != INF){
				printf("Arco: %2d->%2d Custo: %2d\n", v, w, G->adj[v][w]);
			}
		}
   }
}


int distanciaMinima(Grafo G, int dist[], int Z[]) 
{ 
   int minimo = INF, indiceMenorValor; 
   int v;
   for (v = 1; v <= G->V; v++) 
	 if (Z[v] == 0 && dist[v] <= minimo) 
		 minimo = dist[v], indiceMenorValor = v; 
   
   return indiceMenorValor; 
} 
   
   
void mostraCaminho(int anterior[], int t) 
{ 
	if (anterior[t] == - 1){
		printf("\nCaminho: ");
		return;
	}
	
	mostraCaminho(anterior, anterior[t]); 
	printf("(%d %d) ", anterior[t], t); 
} 
   

void Dijkstra(Grafo G, int s, int t) 
{

	int dist[(G->V)+1];     
	int Z[(G->V)+1]; 
	int anterior[(G->V)+1]; 
	
	int i, j, v;
	
	for (i = 1; i <= G->V; i++){
		anterior[i] = -1; 
		dist[i] = INF, Z[i] = 0; 
	}
	
	dist[s] = 0; 
	
	for (j = 1; j <= G->V; j++) { 
		
		int u = distanciaMinima(G, dist, Z); 
		Z[u] = 1; 
		
		for (v = 1; v <= G->V; v++){
 
			if (!Z[v] && G->adj[u][v] != INF && dist[u] != INF && dist[u]+G->adj[u][v] < dist[v]){
				anterior[v] = u; 
				dist[v] = dist[u] + G->adj[u][v]; 
			}
		}
		
	} 
	

	printf("\nO custo mínimo do vértice %d ao vértice %d é: %d\n", s, t, dist[t]);
	mostraCaminho(anterior, t); 
	
	
	/* Espera o usuario pressionar uma tecla para voltar ao menu principal */
	printf("\n\n[i] Pressione <ENTER> para voltar ao MENU DE OPCOES...");
	setbuf(stdin,NULL);
	getchar();
	

} 

void leituraArquivo(){
	/**   Lê o nome do arquivo e, ao localizá-lo, lê o grafo contido no mesmo,
	 *    bem como os custos de seus arcos, e encontra um caminho de custo mínimo
		  utilizando o algoritmo de Dijkstra.
	 */

	/* Cabeçalho */
	limpaTela();
	printf("### Receber grafo a partir de um arquivo ###\n\n");

	/* Variáveis para manipulação do arquivo */
	char *nomeArquivo;
	FILE *file;

	/* Variáveis para leitura e manipulação dos dados contidos no arquivo */
	int vertices, arcos, origem, destino;
	vertice v, w;
	int custo;
	Grafo G;

	/* Variáveis auxiliares */
	int i=0;
	
	nomeArquivo = malloc(sizeof(char)*35); /* Aloca string com até 35 caracteres (valor arbitrário) */

	if(nomeArquivo == NULL){
		printf("[x] Falha! Não há memória disponível no sistema");
		free(nomeArquivo);
		return;
	}
	setbuf(stdin,NULL);
	printf("Digite o nome do arquivo de texto (SEM SUA EXTENSÃO): ");
	scanf(" %s", nomeArquivo);   //Lê o nome do arquivo;

	strcat(nomeArquivo,".txt\0"); //Adiciona a extensão '.txt' mais caractere '\0' (final da string) ao nome do arquivo;

	file = fopen(nomeArquivo,"r"); //Abre arquivo no modo de leitura;

	if(file == NULL){ /* Arquivo não encontrado */
		free(nomeArquivo);
		printf("\n\n[!] Arquivo não localizado");
		printf("\n[i] Verifique se o arquivo existe ou se você digitou o nome corretamente");
		printf("\n\n[i] Pressione <ENTER> para voltar ao MENU DE OPCÕES...");
		setbuf(stdin,NULL);
		getchar();

		return;
	}
	else{
		printf("\n\tArquivo: %s\t",nomeArquivo);


	/*Lê a primeira linha do arquivo, contendo a quantidade de vértices,
	a quantidade de arcos, o vértice origem e o vértice destino. */
		fscanf(file,"%d %d %d %d",&vertices, &arcos, &origem, &destino); 

		printf("\nVértices: %d\tArcos: %d\t Origem: %d\t Destino: %d\n", vertices, arcos, origem, destino);
		G = inicializaGrafo(vertices);
		while(i < arcos){ /* Lê as próximas m linhas contendo os arcos do grafo */
			/* Lê um arco do grafo */
			fscanf(file,"%d %d %d",&v, &w, &custo);
			insereArco(G, v, w, custo);
			i++;
			setbuf(stdin,NULL);
		}
		
		mostraGrafo(G);
	   
		/*chama a função Dijkstra passando o vértice origem e o vértice destino, 
			o que vai nos devolver o custo mínimo para sair da origem e chegar ao destino. */
		Dijkstra(G, origem, destino); 

		fclose(file); //Fecha o arquivo
	}
}


/** FUNÇÃO PRINCIPAL */
int main(){
	setlocale(LC_ALL, "portuguese");
	int finalizarPrograma = 0; //Flag para quando o usuário desejar finalizar o programa.
	

	leituraArquivo();
	return 0;
} /* Fim main() */
