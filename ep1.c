/**
 *   TRABALHO DE GRAFOS - ENGENHARIA DE COMPUTAÇÃO - TARDE
 *
 *   Desenvolvido na IDE DEV-C++
 *
 *   EQUIPE:
 *       - Cláudia Mariana Costa Maia
 *       - Jorge Girão Limaverde Lima
 *		 - Thalia Nascimento de Sousa Freitas
 *       - Ulric Marques Ferreira
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <limits.h>

/* Vértices de grafos são representados por objetos do tipo vertice. */ 
#define vertice int
#define INF INT_MAX

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura grafo representa um grafo. 
	O campo adj é um ponteiro para a matriz de adjacências do grafo. 
	O campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */
	struct grafo {
	   int V; 
	   int A; 
	   int **adj; 
	};
	
	/* Um Grafo é um ponteiro para um grafo, ou seja, um Grafo contém o endereço de um grafo. */
	typedef struct grafo *Grafo;

void limpaTela(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função alocaMatriz() aloca uma matriz com linhas 1..r e colunas 1..c. 
Cada elemento da matriz recebe valor val. */
static int **alocaMatriz( int r, int c, int val) { 
   vertice i, j;
   int **m = malloc( r * sizeof (int *));
   for (i = 1; i <= r; ++i) 
      m[i] = malloc( c * sizeof (int));
   for (i = 1; i <= r; ++i)
      for (j = 1; j <= c; ++j)
         m[i][j] = val;
   return m;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função inicializaGrafo() constrói um grafo com vértices 1,2 .. V e nenhum arco. */
Grafo inicializaGrafo( int V) { 
   Grafo G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = alocaMatriz( V, V, INF);
   return G;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função insereArco() insere um arco v-w com custo c no grafo G.
A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */

void insereArco( Grafo G, vertice v, vertice w, int c) { 
   if (G->adj[v][w] == INF) {
      G->adj[v][w] = c; 
      G->A++;
   }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função removeArco() remove do grafo G o arco v-w.
A função supõe que v e w são distintos, positivos e menores que G->V. Se não existe arco v-w, a função não faz nada. */
void removeArco( Grafo G, vertice v, vertice w) { 
   if (G->adj[v][w] != INF) {
      G->adj[v][w] = -1; 
      G->A--;
   }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função mostraGrafo() imprime, para cada vértice v do grafo G,
em uma linha, todos os vértices adjacentes a v, além dos custos de cada arco. */
void mostraGrafo( Grafo G) { 
   vertice v,w;
   for (v = 1; v <= G->V; ++v) {
      printf( "%2d:", v);
      for (w = 1; w <= G->V; ++w)
         if (G->adj[v][w] != INF) 
            printf( " %2d", w);
      printf( "\n");
   }
   
   printf( "\n");
   
   for (v = 1; v <= G->V; ++v) {
      for (w = 1; w <= G->V; ++w)
         if (G->adj[v][w] != INF){
            printf("Arco: %2d->%2d Custo: %2d", v, w, G->adj[v][w]);
			printf("\n");
		}
   }
}

int distanciaMinima(Grafo G, int dist[], bool Z[]) 
{ 
   int minimo = INF, indiceMenorValor; 
   int v;
   for (v = 1; v <= G->V; v++) 
     if (Z[v] == false && dist[v] <= minimo) 
         minimo = dist[v], indiceMenorValor = v; 
   
   return indiceMenorValor; 
} 
   
   
void mostraCaminho(int anterior[], int j) 
{ 
    if (anterior[j] == - 1){
    	printf("%d ", j);  
        return;
	}
    mostraCaminho(anterior, anterior[j]); 
    
    printf("%d ", j); 
} 
   
int mostraSolucao(int dist[], int n, int anterior[], int s, int t) 
{ 
    mostraCaminho(anterior, t); 
} 


int mostraDistancias(int dist[], bool Z[], int anterior[], int n) 
{ 
	int i;
   	printf("\nDistâncias\n"); 
   	for (i = 1; i <= n; i++) 
     	printf("%d ", dist[i]); 
	printf("\n");
	
	printf("Vetor Z\n"); 
   	for (i = 1; i <= n; i++) 
     	printf("%d ", Z[i]); 
	printf("\n");
	
	printf("Anterior\n"); 
   	for (i = 1; i <= n; i++) 
     	printf("%d ", anterior[i]); 
	printf("\n");
} 
   
 
void Dijkstra(Grafo G, int s, int t) 
{ 
	int dist[(G->V)+1];     
	bool Z[(G->V)+1]; 
	int anterior[(G->V)+1]; 
	
	int i, j, v;
	
	for (i = 1; i <= G->V; i++){
		anterior[i] = -1; 
		dist[i] = INF, Z[i] = false; 
	}
	
	dist[s] = 0; 
	
	for (j = 1; j <= G->V; j++) { 
		
		int u = distanciaMinima(G, dist, Z); 
//		printf("\nNo início da iteração sobre o vértice %d:", u);
//		mostraDistancias(dist, Z, anterior,G->V);
		Z[u] = true; 
		
		for (v = 1; v <= G->V; v++){
 
			if (!Z[v] && G->adj[u][v] != INF && dist[u] != INF && dist[u]+G->adj[u][v] < dist[v]){
				anterior[v] = u; 
		    	dist[v] = dist[u] + G->adj[u][v]; 
			}
		}
		
//		printf("\nAo final da iteração:");
//		mostraDistancias(dist, Z, anterior, G->V);
	} 
	
	
	printf("O custo mínimo de %d a %d é: %d\n", s, t, dist[t]);
	mostraSolucao(dist, G->V, anterior, s ,t); 
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
    int n, m, s, t;
    vertice v, w;
    int c;
    Grafo G;

    /* Variáveis auxiliares */
    int i=1, j=1;
    int aux=0; //Variável auxiliar, para ler a primeira linha do arquivo
    
    nomeArquivo = malloc(sizeof(char)*35); /* Aloca string com até 35 caracteres (valor arbitrário) */

    if(nomeArquivo == NULL){
        printf("[x] Falha! Nao ha memoria disponivel no sistema");
        free(nomeArquivo);
        return;
    }
    setbuf(stdin,NULL);
    printf("Digite o nome do arquivo de texto (SEM SUA EXTENSAO): ");
    gets(nomeArquivo);   //Lê o nome do arquivo;

    strcat(nomeArquivo,".txt\0"); //Adiciona a extensão '.txt' mais caractere '\0' (final da string) ao nome do arquivo;

    file = fopen(nomeArquivo,"r"); //Abre arquivo no modo de leitura;

    if(file == NULL){ /* Arquivo não encontrado */
        free(nomeArquivo);
        printf("\n\n[!] Arquivo nao localizado");
        printf("\n[i] Verifique se o arquivo existe ou se voce digitou o nome corretamente");
        printf("\n\n[i] Pressione <ENTER> para voltar ao MENU DE OPCOES...");
        setbuf(stdin,NULL);
        getchar();

        return;
    }
    else{
        printf("\n\tArquivo: %s\t",nomeArquivo);

        while(!feof(file)){ /* Lê os dados do arquivo enquanto não chega no final do mesmo */
            if(aux==0){
                fscanf(file,"%d %d %d %d",&n, &m, &s, &t); //Lê a primeira linha do arquivo, contendo n, m, s e t.
                G = inicializaGrafo(n);

                printf("Numero de vertices: %d\n",n);
                aux++; //Atualiza 'aux', para que este laço não seja mais executado nas próximas iterações.

            } else{
                /* Lê uma aresta do grafo */
                fscanf(file,"%d %d %d",&v, &w, &c);
                insereArco(G, v, w, c);
                //v = 0; w = 0; c = 0;  //Reinicialização da variável, para receber novo valor na próxima iteração.
                setbuf(stdin,NULL);
            }
        }
        
        mostraGrafo(G);
       
        Dijkstra(G, s, t); /*chama a função dijkstra passando o vértice origem, o que vai nos devolver o custo mínimo 
						pra sair da origem e chegar em todos os outros vértices */
        fclose(file); //Fecha o arquivo
	}
}

 char menuDeOpcoes(){
    /** Exibe o menu de opções, lê a opção escolhida pelo usuário e retorna essa opção */

    char opcao;

    //Mostra o menu de opções. Repete o processo enquanto a opção escolhida pelo usuário não for válida.
    do{
        //Monta menu.
        limpaTela();
        printf("### GRAFOS ###\n\n");
        printf("### MENU DE OPCOES ###\n\n");
        printf("C - Caminho minimo\n");
        printf("F - Finalizar\n");
        printf("\n[i] Escolha uma opcao acima e pressione <ENTER>: ");

        setbuf(stdin,NULL);
        opcao = toupper(getchar()); //Lê a opção digitada pelo usuário e a transforma em letra maiúscula.

        /* Exibe aviso de advertência, caso a opção escolhida pelo usuário seja inválida */
        if((opcao!='C') && (opcao!='F')){
            printf("#");
            printf("\n\n[!] Opcao invalida\n");
            printf("[i] Pressione <ENTER> e tente novamente...");
            setbuf(stdin,NULL);
            getchar();
        }
    //Testa validade. Se a opção escolhida for válida, o laço termina. Caso contrário, mostra o menu novamente.
    } while((opcao!='C') && (opcao!='F'));

    return opcao;
} /* Fim menuDeOpcoes() */

 /* ===================== FIM SEÇÃO 04 ===================== */


/** FUNÇÃO PRINCIPAL */
int main(){
    setlocale(LC_ALL, "portuguese");
    int finalizarPrograma = 0; //Flag para quando o usuário desejar finalizar o programa.
    

    /* Laço do-while: Chama a função 'menuDeOpções' e abre a função correspondente à escolha do usuário.
     * Repete o processo enquanto o mesmo não desejar finalizar o programa.
     */
    do{
        switch(menuDeOpcoes()){
            //Opção 'CAMINHO MINIMO'
            case 'C':
                leituraArquivo();
                break;

            //Opção 'FINALIZAR'
            case 'F':
                printf("Finalizar\n");
                finalizarPrograma = 1;
                break;
        }
    //Testa validade para saber se o usuário deseja finalizar o programa.
    } while(!finalizarPrograma);

	return 0;
} /* Fim main() */
