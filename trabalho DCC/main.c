/*

    * Cada frasco poder� ter somente 4 por��es de �gua, mesmo sendo da mesma cor
    * De acordo que o n�vel aumenta, a quantidade de frascos tamb�m ir� aumentar para dificultar o jogo

*/

// BIBLIOTECAS UTILIZADAS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

//DECLARA��O DAS CONSTANTES
#define QUANTIDADE_CORES 26
#define QUANTIDADE_PORCOES 4

//DECLARA��O DAS MINHAS ESTRUTURAS
typedef struct
{
    char nomeJogador[100];
    int faseJogo;

}DadosJogador;

//DECLARA��O DAS FUN��ES UTILIZADAS NO PROGRAMA
void constroiFrascos(int quantFrascos, int quantFrascosVazios, int numFase, char nomeJogador[]);
void jogoFase1(char nomeJogador[]);


//FUN��O PRINCIPAL DO PROGRAMA
int main()
{
    DadosJogador jogador;
    int gameContinua = 0;

    printf("informe o seu nome antes de come�ar o jogo: ");
    scanf("%s",jogador.nomeJogador);
    printf("Digite 1 para ir continuar o jogo ou zero para finalizar: ");
    scanf("%d",&gameContinua);

    if(gameContinua == 1)
    {
        jogoFase1();
    }

    return 0;
}

//UTILIZA��O DAS FUN��ES DECLARADAS
void constroiFrascos(int quantFrascos, int quantFrascosVazios, int numFase, char nomeJogador[])
{
    int quantFrascosCheios = quantFrascos - quantFrascosVazios;//verifica quantis frascos cheios ter�o na fase
    int quantCor = quantFrascosCheios; //armazena a quantidade de cores que ser�o utilizadas de acordo com a quantidade de frascos cheios que ter�
    int sorteiaCor[quantCor], indiceSorteado = 0;//vetor para armazenar as cores que ser�o utlizadas
    int frascosArmazena[QUANTIDADE_PORCOES][quantFrascos+1]; //conta quantas vezes a cor ja foi utilizada no sorteio
    char frascos[QUANTIDADE_PORCOES][quantFrascos+1];//vetor que ir� desenhar os frascos na tela
    char cores[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


    printf(" -------------------------------------------\n");
    printf("�                                           �\n");
    printf("�Nome: %s                                   \n",nomeJogador);
    printf("�Fase: %d                                      \n", numFase);
    printf("�                                           �\n");
    printf(" -------------------------------------------\n\n");

    for(int i = 0; i < QUANTIDADE_PORCOES; i++)
    {
        for(int j = 0; j <= quantFrascos; j++)
        {
            frascos[i][j] = '|';
        }
    }

    //armazena no vetor as cores que ser�o utilizadas
    for(int i = 0; i < quantCor; i++)
    {
        sorteiaCor[i] = rand() % QUANTIDADE_CORES; //sorteia a cor que ira ser utilizada
    }

    //coloca o numero da coluna em cima para poder ajudar o usu�rio na hora de informar
    for(int i = 0; i < quantFrascos; i++)
    {
        printf("   %d  ",i);
    }

    printf("\n");

    //desenha os frascos na tela
    for(int i = 0; i < QUANTIDADE_PORCOES; i++)
    {
        for(int j = 0; j <= quantFrascos; j++)
        {
            //verifica para n�o desenhar o cont�do dentro do frasco, uma coluna fora
            if(j < quantFrascosCheios)
            {
                printf("%c",frascos[i][j]);
                indiceSorteado = sorteiaCor[rand() % quantCor];
                frascosArmazena[i][j] = cores[indiceSorteado];
                for(int y = 0; y < 5; y++)
                {
                    printf("%c", cores[indiceSorteado]);
                }
            }
            else if(j >= quantFrascosCheios)
            {
                frascosArmazena[i][j] = '#';
                printf("%c     ",frascos[i][j]);
            }
            else if(j == quantFrascos)
            {
                frascosArmazena[i][j] = '#';
                printf("%c",frascos[i][j]);
            }
        }
        printf("\n");
    }
}

void jogoFase1()
{
    constroiFrascos(3,1,1,jogador.nomeJogador);
}
