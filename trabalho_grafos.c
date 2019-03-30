/**
 *   TRABALHO DE GRAFOS - ENGENHARIA DE COMPUTAÇÃO - TARDE
 *
 *   Desenvolvido na IDE DEV-C++
 *
 *   EQUIPE:
 *       - Cláudia Mariana Costa Maia
 *       - 
 		 -
 *       - Ulric Marques Ferreira
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

void limpaTela(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void mostraCaminho(int path[], int j){ 
    if (path[j]== -1) //a condição de parada é quando path[j] = -1, ou seja, quando chegar em path[0], que é a origem
        return;

    mostraCaminho(path, path[j]); //chama recursivamente a função mostraCaminho pra ir retornando do último vértice do caminho até o primeiro, que é a origem

    printf("%d ", j); 

}

void dijkstra (int Vi){ //recebe a origem, aqui chamada de Vi
    char vis[MAXV]; 	//o vetor de visitados, que vai dizer se já passamos pelo vértice em questão(0 para não visitado ou 1 para visitado)
    memset (vis, 0, sizeof (vis)); 	// inicializa todo o vetor vis com 0 (ninguém foi visitado ainda)
    memset (dis, inf, sizeof (dis));     //inicializa todas as distancias com infinito(não sabemos nenhuma distância ainda)
    dis[Vi] = 0; // a distância da origem até ela mesma é 0
    path[0] = -1; //o caminho pra chegar da origem até ela mesma é -1, pra servir como condição de parada para a função mostraCaminho
    int t, i;
    for (t = 1; t < A+1; t++){
        int v = -1; //inicializa a variável v, que será usada para percorrer o grafo
        for (i = 1; i < A+1; i++) 
            if (!vis[i] && (v < 0 || dis[i] < dis[v])) //se i não foi visitado e 
                v = i;
        vis[v] = 1; //marca o vértice v como visitado
        for (i = 1; i < A+1; i++)  //laço que verifica as ligações do vértice v e escolhe a que tem o menor custo pra guardar no vetor dis
            if (matriz[v][i] && dis[i] > dis[v] + matriz[v][i]){
                dis[i] = dis[v] + matriz[v][i];
                path[i]  = v;
            }
    }

}

void sistemaLinear(){
    /**   Lê o nome do arquivo e, ao localizá-lo, lê o Sistema Linear contido no mesmo,
     *    bem como sua respectiva dimensao, e o resolve através do método de Jordan.
     */

    /* Cabeçalho */
    limpaTela();
    printf("### Receber grafo a partir de um arquivo ###\n\n");

    /* Variáveis para manipulação do arquivo */
    char *nomeArquivo;
    FILE *file;

    /* Variáveis para leitura e manipulação dos dados contidos no arquivo */
    int n;
    int coeficiente=0;
    double **matriz;
    double *vetorSolucao;

    /* Variáveis auxiliares */
    int i=0, j=0;
    int aux=0; //Variável auxiliar, para ler a primeira linha do arquivo (dimensao do sistema)
    int *vetorIndices; //Vetor utilizado para associar cada coluna da matriz a sua respectiva variável do sistema 


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
                fscanf(file,"%d",&n); //Lê dimensao da matriz (primeira linha do arquivo);
                matriz = alocaMatriz(n,n+1);
                vetorSolucao = malloc(sizeof(double)*n);

                printf("Dimensao do sistema: %dx%d\n",n,n);

                if(matriz == NULL || vetorSolucao == NULL){ /* Falta de memória */
                    printf("\n[x] Falha! Nao ha memoria disponivel no sistema");
                    printf("\n\n[i] Pressione <ENTER> para voltar ao MENU DE OPCOES...");
                    setbuf(stdin,NULL);
                    getchar();
                    return;
                }
                aux++; //Atualiza 'aux', para que este laço não seja mais executado nas próximas iterações.

            } else{
                /* Lê a matriz contida arquivo */
                fscanf(file,"%d",&coeficiente);
                matriz[i][j] = coeficiente;

                coeficiente = 0; //Reinicialização da variável, para receber novo valor na próxima iteração.
                setbuf(stdin,NULL);

                /* Atualiza i e j para atribuir os valores às posições corretas na matriz */
                j++;
                if(j>n){
                    i++;
                    j = 0;
                }
            }
        }
        fclose(file); //Fecha o arquivo

 char menuDeOpcoes(){
    /** Exibe o menu de opções, lê a opção escolhida pelo usuário e retorna essa opção */

    char opcao;

    //Mostra o menu de opções. Repete o processo enquanto a opção escolhida pelo usuário não for válida.
    do{
        //Monta menu.
        limpaTela();
        printf("### CALCULO NUMERICO ###\n\n");
        printf("### MENU DE OPCOES ###\n\n");
        printf("C - Conversao\n");
        printf("S - Sistema Linear\n");
        printf("E - Equacao Algebrica\n");
        printf("F - Finalizar\n");
        printf("\n[i] Escolha uma opcao acima e pressione <ENTER>: ");

        setbuf(stdin,NULL);
        opcao = toupper(getchar()); //Lê a opção digitada pelo usuário e a transforma em letra maiúscula.

        /* Exibe aviso de advertência, caso a opção escolhida pelo usuário seja inválida */
        if((opcao!='C') && (opcao!='S') && (opcao!='E') && (opcao!='F')){
            printf("#");
            printf("\n\n[!] Opcao invalida\n");
            printf("[i] Pressione <ENTER> e tente novamente...");
            setbuf(stdin,NULL);
            getchar();
        }
    //Testa validade. Se a opção escolhida for válida, o laço termina. Caso contrário, mostra o menu novamente.
    } while((opcao!='C') && (opcao!='S') && (opcao!='E') && (opcao!='F'));

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
            //Opção 'CONVERSÃO'
            case 'C':
                converteBase();
                break;

            //Opção 'SISTEMA LINEAR'
            case 'S':
                sistemaLinear();
                break;

            //Opção 'EQUAÇÃO ALGÉBRICA'
            case 'E':
                equacaoAlgebrica();
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
