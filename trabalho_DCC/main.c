/**
            WATER SORT PUZZLE
    * Matéria: DCC 120 e DCC 119
    * Trabalho feito pelos alunos Augusto Benedito Carvalho da Silva e Quezia Emanuelly da Silva Oliveira
**/

///BIBLIOTECAS UTILIZADAS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

///DECLARAÇÃO DAS CONSTANTES UTILIZADAS
#define QUANTIDADE_CORES 26
#define QUANTIDADE_PORCOES 4
#define QUANTIDADE_MAX_COLUMN 100
#define MAX_FASES 15

///DECLARAÇÃO DAS ESTRUTURAS UTILIZADAS NO PROGRAMA
typedef struct
{
    char nomeJogador[100];


}DadosJogador;

///DECLARAÇÃO DAS FUNÇÕES UTILIZADAS NO PROGRAMA
void constroiFrascos(int quantFrascos, int quantFrascosVazios); //função que ira desenhar os frascos na tela
int VerificaCor(int cores[]); //função que ira verificar se todas as cores ja foram utilizadas
void atualizaFrascos(int quantFrascos, int numFase, DadosJogador Jogador, float progresso); //função que irá desenhar os frascos na tela
int verificaVencedor(int quantFrascos); //função que verifica se o jogador venceu a fase em que ele esta
int jogoFase(DadosJogador nomeJogador, int numFase, float progresso); //função responsavel de rodar as fases do jogo
int verificaJogada(int linhaSaida, int colunaSaida, int linhaChegada, int colunaChegada, int quantFrascos); //verifica se a jogada é valida
void realizaJogadas(int linhaSaida, int colunaSaida, int linhaChegada, int colunaChegada); //realiza as jogadas feitas pelo jogador

///DECLARAÇÃO DAS VARIÁVEIS GLOBAIS
char frascosArmazena[QUANTIDADE_PORCOES][QUANTIDADE_MAX_COLUMN]; //matriz que será utilizado para fazer as jogadas
int quantCor = 0; //armazena a quantidade de cores que será utilizadas nas fases

///FUNÇÃO PRINCIPAL DO PROGRAMA
int main()
{
    DadosJogador jogador;
    int gameContinua = 1, numFase = 0;
    float progresso = 0;

    printf("informe o seu nome antes de comecar: ");
    scanf("%s",jogador.nomeJogador);

    printf("\nOla prototipo C-%s, voce e o primeiro Android criado pela empresa ####, a partir dos dias voce sera testado com um jogo simples de combinar para verificar suas capacidades motoras, de raciocinio logico e resolucao de problemas, espero que voce consiga\n", jogador.nomeJogador);

    while(gameContinua == 1 && numFase <= MAX_FASES)
    {
        numFase++;
        printf("\nDigite 1 para iniciar a fase %d ou zero se quiser finalizar o jogo: ", numFase);
        scanf("%d",&gameContinua);
        if(gameContinua == 0)
        {
            break;
        }
        else
        {
            progresso = (numFase - 1) * 6.667;
            jogoFase(jogador,numFase,progresso);
        }
    }

    if(numFase == 15)
    {
        printf("\n\nPARABENS VOCÊ CONSEGUIU, VOCÊ É O PRIMEIRO PROTÓTIPO DO MUNDO PARA TRAZER A ESPERANÇA DO MUNDO E AJUDAR AS PESSOAS!!\n\n");
    }
    else
    {
        printf("Parabens por ter completado ate a fase %d, mas infelizmente voce nao passou no teste :(\n", numFase-1);
    }

}

/// ******************************* UTILIZAÇÃO DAS FUNÇÕES DECLARADAS ******************************************

///ARMAZENA AS CORES NA MATRIZ QUE SERÁ UTILIZADA PARA AS JOGADAS
void constroiFrascos(int quantFrascos, int quantFrascosVazios)
{
    int quantFrascosCheios = quantFrascos - quantFrascosVazios;//verifica quantos frascos cheios terão na fase
    quantCor = quantFrascosCheios; //armazena a quantidade de cores que serão utilizadas de acordo com a quantidade de frascos cheios
    int sorteiaCor[quantCor], indiceSorteado = 0;//vetor para armazenar as cores que serão utlizadas
    char cores[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'}; //vetor que armazenas as cores utilizadas no jogo
    int quantVezesCor[QUANTIDADE_CORES] = {0}; //armazena quantas vezes as cores sorteadas ja foram mostradas na tela, cada cor só poder ser utilizadas 4 vezes

    srand(time(NULL));
    //armazena no vetor as cores que serão utilizadas
    for(int i = 0; i < quantCor; i++)
    {
        sorteiaCor[i] = rand() % QUANTIDADE_CORES; //sorteia a cor que ira ser utilizada e armazena no vetor
    }

    //armazena na matriz das jogadas as cores que serão utilizadas
    for(int i = 0; i < QUANTIDADE_PORCOES; i++)
    {
        for(int j = 0; j <= quantFrascos; j++)
        {
            //verifica para não armazenar o contúdo dentro do frasco a partir da última coluna
            if(j < quantFrascosCheios)
            {
                indiceSorteado = sorteiaCor[rand() % quantCor];
                quantVezesCor[indiceSorteado] += 1;

                //verifica para não armazenar mais do que 4 vezes a mesma cor
                if(quantVezesCor[indiceSorteado] <=  QUANTIDADE_PORCOES)
                {
                    frascosArmazena[i][j] = cores[indiceSorteado];
                }
                //manda para a função que ira verificar se todas as cores ja foram usadas
                else if(VerificaCor(quantVezesCor) == 1)
                {
                    //caso alguma cor ainda não tenha sido usada totalmente, essa parte roda até achar uma cor que não tenha sido usada por completo
                    do
                    {
                        indiceSorteado = sorteiaCor[rand() % quantCor];
                        quantVezesCor[indiceSorteado] += 1;
                    }while(quantVezesCor[indiceSorteado] > QUANTIDADE_PORCOES);

                    //e quando encontrar essa cor armazena na matriz das jogadas
                    frascosArmazena[i][j] = cores[indiceSorteado];
                }

            }
            else if(j >= quantFrascosCheios && j < quantFrascos)
            {
                frascosArmazena[i][j] = '#'; //armazena um # nas posições vazias da matriz
            }
        }
        printf("\n");
    }
}

///VERIFICA SE TODAS AS CORES JA FORAM USADAS
int VerificaCor(int cores[])
{
    for(int i = 0; i < QUANTIDADE_CORES; i++)
    {
        if(cores[i] != QUANTIDADE_PORCOES)
        {
            return 1;
        }
    }

    return 0;
}

///ATUALIZA OS FRASCOS DE ACORDO COM AS JOGADAS DO JOGADOR
void atualizaFrascos(int quantFrascos, int numFase, DadosJogador Jogador, float progresso)
{

    system("cls");
    //system("clear");

    printf(" -------------------------------------------\n");
    printf("|                                           |\n");
    printf("|Prototipo: C-%s                                   \n",Jogador.nomeJogador);
    printf("|Fase: %d                                      \n", numFase);
    printf("|Progresso do jogo: %.2f%%                                      \n", progresso);
    printf("|                                           |\n");
    printf(" -------------------------------------------\n\n");

    //coloca o numero da coluna em cima para poder ajudar o jogador na hora de informar
    for(int i = 0; i < quantFrascos; i++)
    {
        printf("    %d       ",i);
    }

    printf("\n\n");

    //desenha os frascos na tela junto com as cores de acordo com a matriz das jogadas
    for(int i = 0; i < QUANTIDADE_PORCOES; i++)
    {
        for(int j = 0; j < quantFrascos; j++)
        {
            printf("| ");
            if(j < quantFrascos)
            {
                if(frascosArmazena[i][j] == '#')
                {
                    printf("      ");
                    printf("|   ");
                }
                else
                {
                    for(int x = 0; x < 3; x++)
                    {
                        printf("%c ", frascosArmazena[i][j]);
                    }
                    printf("|   ");
                }
            }
        }
        printf("\n");
    }

    /*
    for(int i = 0; i < QUANTIDADE_PORCOES; i++)
    {
        for(int j = 0; j < quantFrascos; j++)
        {
            printf("%c ", frascosArmazena[i][j]);
        }
        printf("\n");
    }
    */
}

///FUNÇÃO QUE IRÁ RODAR AS FASES DO JOGO
int jogoFase(DadosJogador nomeJogador, int numFase, float progresso)
{
    int quantFrascos = 0, quantFrascosVazios = 0; //armazena a quantidade de frascos de acordo com a fase
    int linhaSaida = 0, linhaChegada = 0; //armazena a linha das colunas que serão utilizadas nas jogadas
    int colunaSaida = 0, colunaChegada = 0; //armazena as colunas que serão utilizadas nas jogadas

    switch(numFase)
    {
        case 1:
        case 2:
            quantFrascos = 3;
            quantFrascosVazios = 1;
            break;
        case 3:
        case 4:
            quantFrascos = 5;
            quantFrascosVazios = 2;
            break;
        case 5:
        case 6:
            quantFrascos = 6;
            quantFrascosVazios = 2;
            break;
        case 7:
        case 8:
        case 9:
            quantFrascos = 7;
            quantFrascosVazios = 2;
            break;
        default:
            quantFrascos = 8;
            quantFrascosVazios = 3;
    }

    constroiFrascos(quantFrascos,quantFrascosVazios);
    atualizaFrascos(quantFrascos,numFase,nomeJogador,progresso);

    //o jogo roda enquanto o jogador não tiver vencido a fase
    while(verificaVencedor(quantFrascos) != 0)
    {

        printf("\ninforme a coluna da cor que deseja trocar de posicao: ");
        scanf("%d",&colunaSaida);
        printf("informe a coluna do frasco que ira receber a cor: ");
        scanf("%d",&colunaChegada);

        //pega a primeira linha da coluna selecionada que estiver com conteúdo dentro
        for(int i = 0; i < QUANTIDADE_PORCOES; i++)
        {
            if(frascosArmazena[i][colunaSaida] != '#')
            {
                linhaSaida = i;
                break;
            }
        }

        //pega a primeira linha da coluna selecionada que estiver vazia, comaça a verificar da última linha para a primeira
        for(int i = QUANTIDADE_PORCOES-1; i >= 0; i--)
        {
            if(frascosArmazena[i][colunaChegada] == '#')
            {
                linhaChegada = i;
                break;
            }
        }

        //verifica se a jogada realizada pelo jogador foi válida, se não estiver sido informa uma mensagem de erro e o jogador poderá jogar novamente
        if((verificaJogada(linhaSaida,colunaSaida,linhaChegada,colunaChegada,quantFrascos)) == 0)
        {
            realizaJogadas(linhaSaida,colunaSaida,linhaChegada,colunaChegada);
            atualizaFrascos(quantFrascos,numFase,nomeJogador,progresso);
        }
        else
        {
            printf("Jogada invalida, jogue novamente");
        }

    }

    printf("\nPARABENS VC VENCEU A FASE %d!!!!\n", numFase);

    return 0;

}

///VERIFICA SE A JOGADA REALIZADA PELO JOGADOR É VÁLIDA
int verificaJogada(int linhaSaida, int colunaSaida, int linhaChegada, int colunaChegada, int quantFrascos)
{
    //verifics se a linha que irá receber a cor for a última
    if(linhaChegada != QUANTIDADE_PORCOES-1)
    {
        //verifica se as colunas indicadas pelo jogador foram colunas válidas para as fases
        if(colunaChegada < 0 || colunaChegada >= quantFrascos)
        {
            return 1;
        }
        //verifica para que o jogador não possa colocar uma cor diferente em cima da outra
        else if(frascosArmazena[linhaSaida][colunaSaida] == frascosArmazena[linhaChegada+1][colunaChegada] && frascosArmazena[linhaChegada][colunaChegada] == '#')
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }

    return 0;
}

///REALIZA AS JOGADAS DO JOGADOR
void realizaJogadas(int linhaSaida, int colunaSaida, int linhaChegada, int colunaChegada)
{
    char aux; //armazena o caractere para poder fazer a troca na jogada
    char compara = frascosArmazena[linhaSaida][colunaSaida]; //armazena o valor do caractere que vai ser mandado para o outro frasco, para poder comparar
    int cont = 0;

    //realiza a mudança até o caractere de saída seja diferente do que foi escolhido e também até ter espaço no outro frasco para poder receber essa quantidade de cor
    while(compara == frascosArmazena[linhaSaida+cont][colunaSaida] && frascosArmazena[linhaChegada-cont][colunaChegada] == '#')
    {
        printf("%c \n", frascosArmazena[linhaSaida+cont][colunaSaida]);
        //printf("%c \n", frascosArmazena[linhaChegada-cont][colunaChegada]);
        aux = frascosArmazena[linhaSaida+cont][colunaSaida];
        frascosArmazena[linhaSaida+cont][colunaSaida] = frascosArmazena[linhaChegada-cont][colunaChegada];
        frascosArmazena[linhaChegada-cont][colunaChegada] = aux;
        cont++;
    }
}

///VERIFICA SE O JOGADOR VENCEU A FASE EM QUE ESTÁ JOGANDO
int verificaVencedor(int quantFrascos)
{
    char varialvelVencedor; //recebe o caractere sempre da primeira linha de cada coluna para poder comprar se o jogador venceu

    for(int j = 0; j < quantFrascos; j++)
    {
        varialvelVencedor = frascosArmazena[0][j];
        if(frascosArmazena[1][j] != varialvelVencedor || frascosArmazena[2][j] != varialvelVencedor || frascosArmazena[3][j] != varialvelVencedor)
        {
            return 1;
        }
    }

    return 0;
}
