/**
 *   TRABALHO DE GRAFOS - ENGENHARIA DE COMPUTA��O - TARDE
 *
 *   Desenvolvido na IDE DEV-C++
 *
 *   EQUIPE:
 *       - Cl�udia Mariana Costa Maia
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
    if (path[j]== -1) //a condi��o de parada � quando path[j] = -1, ou seja, quando chegar em path[0], que � a origem
        return;

    mostraCaminho(path, path[j]); //chama recursivamente a fun��o mostraCaminho pra ir retornando do �ltimo v�rtice do caminho at� o primeiro, que � a origem

    printf("%d ", j); 

}

void dijkstra (int Vi){ //recebe a origem, aqui chamada de Vi
    char vis[MAXV]; 	//o vetor de visitados, que vai dizer se j� passamos pelo v�rtice em quest�o(0 para n�o visitado ou 1 para visitado)
    memset (vis, 0, sizeof (vis)); 	// inicializa todo o vetor vis com 0 (ningu�m foi visitado ainda)
    memset (dis, inf, sizeof (dis));     //inicializa todas as distancias com infinito(n�o sabemos nenhuma dist�ncia ainda)
    dis[Vi] = 0; // a dist�ncia da origem at� ela mesma � 0
    path[0] = -1; //o caminho pra chegar da origem at� ela mesma � -1, pra servir como condi��o de parada para a fun��o mostraCaminho
    int t, i;
    for (t = 1; t < A+1; t++){
        int v = -1; //inicializa a vari�vel v, que ser� usada para percorrer o grafo
        for (i = 1; i < A+1; i++) 
            if (!vis[i] && (v < 0 || dis[i] < dis[v])) //se i n�o foi visitado e 
                v = i;
        vis[v] = 1; //marca o v�rtice v como visitado
        for (i = 1; i < A+1; i++)  //la�o que verifica as liga��es do v�rtice v e escolhe a que tem o menor custo pra guardar no vetor dis
            if (matriz[v][i] && dis[i] > dis[v] + matriz[v][i]){
                dis[i] = dis[v] + matriz[v][i];
                path[i]  = v;
            }
    }

}

void sistemaLinear(){
    /**   L� o nome do arquivo e, ao localiz�-lo, l� o Sistema Linear contido no mesmo,
     *    bem como sua respectiva dimensao, e o resolve atrav�s do m�todo de Jordan.
     */

    /* Cabe�alho */
    limpaTela();
    printf("### Receber grafo a partir de um arquivo ###\n\n");

    /* Vari�veis para manipula��o do arquivo */
    char *nomeArquivo;
    FILE *file;

    /* Vari�veis para leitura e manipula��o dos dados contidos no arquivo */
    int n;
    int coeficiente=0;
    double **matriz;
    double *vetorSolucao;

    /* Vari�veis auxiliares */
    int i=0, j=0;
    int aux=0; //Vari�vel auxiliar, para ler a primeira linha do arquivo (dimensao do sistema)
    int *vetorIndices; //Vetor utilizado para associar cada coluna da matriz a sua respectiva vari�vel do sistema 


    nomeArquivo = malloc(sizeof(char)*35); /* Aloca string com at� 35 caracteres (valor arbitr�rio) */

    if(nomeArquivo == NULL){
        printf("[x] Falha! Nao ha memoria disponivel no sistema");
        free(nomeArquivo);
        return;
    }
    setbuf(stdin,NULL);
    printf("Digite o nome do arquivo de texto (SEM SUA EXTENSAO): ");
    gets(nomeArquivo);   //L� o nome do arquivo;

    strcat(nomeArquivo,".txt\0"); //Adiciona a extens�o '.txt' mais caractere '\0' (final da string) ao nome do arquivo;

    file = fopen(nomeArquivo,"r"); //Abre arquivo no modo de leitura;

    if(file == NULL){ /* Arquivo n�o encontrado */
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

        while(!feof(file)){ /* L� os dados do arquivo enquanto n�o chega no final do mesmo */
            if(aux==0){
                fscanf(file,"%d",&n); //L� dimensao da matriz (primeira linha do arquivo);
                matriz = alocaMatriz(n,n+1);
                vetorSolucao = malloc(sizeof(double)*n);

                printf("Dimensao do sistema: %dx%d\n",n,n);

                if(matriz == NULL || vetorSolucao == NULL){ /* Falta de mem�ria */
                    printf("\n[x] Falha! Nao ha memoria disponivel no sistema");
                    printf("\n\n[i] Pressione <ENTER> para voltar ao MENU DE OPCOES...");
                    setbuf(stdin,NULL);
                    getchar();
                    return;
                }
                aux++; //Atualiza 'aux', para que este la�o n�o seja mais executado nas pr�ximas itera��es.

            } else{
                /* L� a matriz contida arquivo */
                fscanf(file,"%d",&coeficiente);
                matriz[i][j] = coeficiente;

                coeficiente = 0; //Reinicializa��o da vari�vel, para receber novo valor na pr�xima itera��o.
                setbuf(stdin,NULL);

                /* Atualiza i e j para atribuir os valores �s posi��es corretas na matriz */
                j++;
                if(j>n){
                    i++;
                    j = 0;
                }
            }
        }
        fclose(file); //Fecha o arquivo

 char menuDeOpcoes(){
    /** Exibe o menu de op��es, l� a op��o escolhida pelo usu�rio e retorna essa op��o */

    char opcao;

    //Mostra o menu de op��es. Repete o processo enquanto a op��o escolhida pelo usu�rio n�o for v�lida.
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
        opcao = toupper(getchar()); //L� a op��o digitada pelo usu�rio e a transforma em letra mai�scula.

        /* Exibe aviso de advert�ncia, caso a op��o escolhida pelo usu�rio seja inv�lida */
        if((opcao!='C') && (opcao!='S') && (opcao!='E') && (opcao!='F')){
            printf("#");
            printf("\n\n[!] Opcao invalida\n");
            printf("[i] Pressione <ENTER> e tente novamente...");
            setbuf(stdin,NULL);
            getchar();
        }
    //Testa validade. Se a op��o escolhida for v�lida, o la�o termina. Caso contr�rio, mostra o menu novamente.
    } while((opcao!='C') && (opcao!='S') && (opcao!='E') && (opcao!='F'));

    return opcao;
} /* Fim menuDeOpcoes() */

 /* ===================== FIM SE��O 04 ===================== */


/** FUN��O PRINCIPAL */
int main(){
    setlocale(LC_ALL, "portuguese");
    int finalizarPrograma = 0; //Flag para quando o usu�rio desejar finalizar o programa.

    /* La�o do-while: Chama a fun��o 'menuDeOp��es' e abre a fun��o correspondente � escolha do usu�rio.
     * Repete o processo enquanto o mesmo n�o desejar finalizar o programa.
     */
    do{
        switch(menuDeOpcoes()){
            //Op��o 'CONVERS�O'
            case 'C':
                converteBase();
                break;

            //Op��o 'SISTEMA LINEAR'
            case 'S':
                sistemaLinear();
                break;

            //Op��o 'EQUA��O ALG�BRICA'
            case 'E':
                equacaoAlgebrica();
                break;

            //Op��o 'FINALIZAR'
            case 'F':
                printf("Finalizar\n");
                finalizarPrograma = 1;
                break;
        }
    //Testa validade para saber se o usu�rio deseja finalizar o programa.
    } while(!finalizarPrograma);

return 0;
} /* Fim main() */
