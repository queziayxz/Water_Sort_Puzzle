/*

            WATER SORT PUZZLE

    * Matéria: DCC 120 e DCC 119
    * Trabalho feito pelos alunos Augusto e Quezia Emanuelly da Silva Oliveira

*/

// BIBLIOTECAS UTILIZADAS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

//DECLARAÇÃO DAS CONSTANTES
#define QUANTIDADE_CORES 26
#define QUANTIDADE_PORCOES 4
#define QUANTIDADE_MAX_COLUMN 100

//DECLARAÇÃO DAS ESTRUTURAS UTILIZADAS NO PROGRAMA
typedef struct
{
    char nomeJogador[100];
    int faseJogo;

}DadosJogador;

//DECLARAÇÃO DAS FUNÇÕES UTILIZADAS NO PROGRAMA
int constroiFrascos(int quantFrascos, int quantFrascosVazios, int numFase, char nomeJogador[]); //função que irá desenhar os frascos na tela
int VerificaCor(int cores[], int quantCor); //função que irá sortear as cores para poder mostrar na tela
void atualizaFrascos(int quantFrascos);
int verificaVencedor();
void jogoFase1(DadosJogador nomeJogador);

//DECLARAÇÃO DAS VARIÁVEIS GLOBAIS
char frascosArmazena[QUANTIDADE_PORCOES][QUANTIDADE_MAX_COLUMN]; //matriz que será utilizado para fazer as jogadas
char frascos[QUANTIDADE_PORCOES][QUANTIDADE_MAX_COLUMN];//matriz que irá desenhar os frascos na tela

//FUNÇÃO PRINCIPAL DO PROGRAMA
int main()
{
    DadosJogador jogador;
    int gameContinua = 0;

    printf("informe o seu nome antes de começar o jogo: ");
    scanf(" %s",jogador.nomeJogador);
    printf("Digite 1 para continuar o jogo ou zero para finalizar: ");
    scanf("%d",&gameContinua);

    if(gameContinua == 1)
    {
        jogoFase1(jogador);
    }

    return 0;
}

//UTILIZAÇÃO DAS FUNÇÕES DECLARADAS
int constroiFrascos(int quantFrascos, int quantFrascosVazios, int numFase, char nomeJogador[])
{
    int quantFrascosCheios = quantFrascos - quantFrascosVazios;//verifica quantos frascos cheios terão na fase
    int quantCor = quantFrascosCheios; //armazena a quantidade de cores que serão utilizadas de acordo com a quantidade de frascos cheios
    int sorteiaCor[quantCor], indiceSorteado = 0;//vetor para armazenar as cores que serão utlizadas
    char cores[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'}; //vetor que armazenas as cores utilizadas no jogo
    int quantVezesCor[QUANTIDADE_CORES] = {0}; //armazena quantas vezes as cores sorteadas ja foram mostradas na tela, cada cor só poder ser utilizadas 4 vezes

    printf(" -------------------------------------------\n");
    printf("³                                           ³\n");
    printf("³Nome: %s                                   \n",nomeJogador);
    printf("³Fase: %d                                      \n", numFase);
    printf("³                                           ³\n");
    printf(" -------------------------------------------\n\n");


    //armazena na matriz as barras para poder desenhar na tela os frascos
    for(int i = 0; i < QUANTIDADE_PORCOES; i++)
    {
        for(int j = 0; j <= quantFrascos; j++)
        {
            frascos[i][j] = '|';
        }
    }

    //armazena no vetor as cores que serão utilizadas
    for(int i = 0; i < quantCor; i++)
    {
        sorteiaCor[i] = rand() % QUANTIDADE_CORES; //sorteia a cor que ira ser utilizada e armazena no vetor
    }

    //coloca o numero da coluna em cima para poder ajudar o usuário na hora de informar
    for(int i = 0; i < quantFrascos; i++)
    {
        printf("      %d     ",i);
    }

    printf("\n\n");

    //desenha os frascos na tela
    for(int i = 0; i < QUANTIDADE_PORCOES; i++)
    {
        for(int j = 0; j <= quantFrascos; j++)
        {
            //verifica para não desenhar o contúdo dentro do frasco a partir da última coluna
            if(j < quantFrascosCheios)
            {
                printf("%c ",frascos[i][j]);
                indiceSorteado = sorteiaCor[rand() % quantCor];
                quantVezesCor[indiceSorteado] += 1;

                //verifica para não mostrar na tela mais do que 4 vezes a mesma cor
                if(quantVezesCor[indiceSorteado] <=  QUANTIDADE_PORCOES)
                {
                    frascosArmazena[i][j] = cores[indiceSorteado];
                    for(int y = 0; y < 5; y++)
                    {
                        printf("%c ", cores[indiceSorteado]);
                    }
                }
                //mando para a função que irá verificar se todas as cores ja foram usadas
                else if(VerificaCor(quantVezesCor,quantCor) == 1)
                {
                    //caso alguma cor ainda não tenha sido usada totalmente, essa parte roda até achar uma cor que não tenha sido usada por completo
                    do
                    {
                        indiceSorteado = sorteiaCor[rand() % quantCor];
                        quantVezesCor[indiceSorteado] += 1;
                    }while(quantVezesCor[indiceSorteado] > QUANTIDADE_PORCOES);

                    //e quando encontrar essa cor, desenho ela na tela e armazeno na matriz das jogadas
                    frascosArmazena[i][j] = cores[indiceSorteado];
                    for(int y = 0; y < 5; y++)
                    {
                        printf("%c ", cores[indiceSorteado]);
                    }
                }

            }
            else if(j >= quantFrascosCheios && j < quantFrascos)
            {
                frascosArmazena[i][j] = '#'; //armazena um # nas posições vazias da matriz
                printf("%c           ",frascos[i][j]);
            }
            else if(j == quantFrascos)
            {
                //frascosArmazena[i][j] = '#'; //armazena um # nas posições vazias da matriz
                printf("%c",frascos[i][j]);
            }
        }
        printf("\n");
    }

    return quantFrascos;
}

//VERIFICA SE TODAS AS CORES JA FORAM USADAS
int VerificaCor(int cores[], int quantCor)
{
    int contCor = 0;

    for(int i = 0; i < QUANTIDADE_CORES; i++)
    {
        if(cores[i] == QUANTIDADE_PORCOES)
        {
            contCor++;
        }
    }

    if(contCor == quantCor)
    {
        //printf("usou tudo");
        return 0;
    }
    else
    {
        //printf("nao usou tudo");
        return 1;
    }
}

void atualizaFrascos(int quantFrascos)
{
    for(int i = 0; i < QUANTIDADE_PORCOES; i++)
    {
        for(int j = 0; j <= quantFrascos; j++)
        {
            printf("%c",frascos[i][j]);
            if(frascosArmazena[i][j] == '#')
            {
                printf("          ");
            }
            else
            {
                for(int x = 0; x < 5; x++)
                {
                    printf("%c ", frascosArmazena[i][j]);
                }
            }
        }
        printf("\n");
    }
}

//FUNÇÃO REFERENTE A FASE 1
void jogoFase1(DadosJogador nomeJogador)
{
    int quantFrascos = 0;
    int indiceSaida = 0, indiceChegada = 0;
    int colunaSaida = 0, colunaChegada = 0; //armazena o indice das colunas que serão utilizadas nas jogadas
    char aux; //armazena o caractere para poder fazer a troca na jogada

                   //quantidade de frascos, quantidade de frascos vazios, numero da vase, nome do jogador
    quantFrascos = constroiFrascos(4,1,1,nomeJogador.nomeJogador);

    printf("informe a coluna da cor que deseja trocar de posicao: ");
    scanf("%d",&colunaSaida);
    printf("informe a coluna do frasco que irá receber a cor: ");
    scanf("%d",&colunaChegada);

    //
    for(int i = 0; i < QUANTIDADE_PORCOES; i++)
    {
        if(frascosArmazena[i][colunaSaida] != '#')
        {
            indiceSaida = i;
            break;
        }
    }

    //
    for(int i = QUANTIDADE_PORCOES-1; i >= QUANTIDADE_PORCOES-1; i--)
    {
        if(frascosArmazena[i][colunaChegada] == '#')
        {
            indiceChegada = i;
            break;
        }
    }

    aux = frascosArmazena[indiceSaida][colunaSaida];
    frascosArmazena[indiceSaida][colunaSaida] = frascosArmazena[indiceChegada][colunaChegada];
    frascosArmazena[indiceChegada][colunaChegada] = aux;


    printf("\n\n");
    atualizaFrascos(quantFrascos);
    verificaVencedor();
}

int verificaVencedor()
{

}
