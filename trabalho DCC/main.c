/*

    * Cada frasco poderá ter somente 4 porções de água, mesmo sendo da mesma cor
    * De acordo que o nível aumenta, a quantidade de frascos também irá aumentar para dificultar o jogo

*/

// BIBLIOTECAS UTILIZADAS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

//DECLARO AS CORES PARA PODER USAR
//#define DARKRED FOREGROUND_RED
//#define DARKBLUE FOREGROUND_BLUE
//#define DARKGREEN FOREGROUND_GREEN
//#define DARKCYAN FOREGROUND_GREEN | FOREGROUND_BLUE
//#define DARKMAGENTA FOREGROUND_RED | FOREGROUND_BLUE
//#define DARKYELLOW FOREGROUND_RED | FOREGROUND_GREEN
//#define DARKGRAY FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define GRAY FOREGROUND_INTENSITY
#define BLUE FOREGROUND_INTENSITY | FOREGROUND_BLUE
#define GREEN FOREGROUND_INTENSITY | FOREGROUND_GREEN
#define CYAN FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define RED FOREGROUND_INTENSITY | FOREGROUND_RED
#define MAGENTA FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE
#define YELLOW FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define WHITE FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

//DECLARAÇÃO DAS FUNÇÕES UTILIZADAS NO PROGRAMA
void constroiFrascos(int quantFrascos, int quantFrascosVazios, int numFase);
void jogoFase1();

//FUNÇÃO PRINCIPAL DO PROGRAMA
int main()
{
    constroiFrascos(3,1,1);

    //system("color 0C");
    return 0;
}

//UTILIZAÇÃO DAS FUNÇÕES DECLARADAS
void constroiFrascos(int quantFrascos, int quantFrascosVazios, int numFase)
{
    char frascos[4][quantFrascos+1];
    int quantFrascosCheios = quantFrascos - quantFrascosVazios;
    char cores[] = "GRAY";"BLUE";"GREEN";"CYAN";"RED";"MAGENTA";"YELLOW";"WHITE";

    //VERIFICAR COMO FUNCIONA ISSO DAQUI
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //SetConsoleTextAttribute(hConsole, YELLOW);
    //printf("This is some nice COLORFUL text, isn't it?");

    /* Restore original attributes */
    //SetConsoleTextAttribute(hConsole, saved_attributes);
    //printf("Back to normal");

    printf("***********************************************************************************************************************\n");
    printf("\n                                                 FASE %d\n\n", numFase);
    printf("***********************************************************************************************************************\n\n");

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < quantFrascos+1; j++)
        {
            frascos[i][j] = '|';
        }
    }

    //desenha os frascos na tela
    for(int i = 0; i < 4; i++)
    {
        printf("     ");
        for(int j = 0; j < quantFrascos+1; j++)
        {
            if(j <= quantFrascosCheios-1)
            {
                SetConsoleTextAttribute(hConsole, cores[i]);
                printf("%c",frascos[i][j]);
                printf("#####");
            }
            else if(j >= quantFrascosCheios)
            {
                SetConsoleTextAttribute(hConsole, saved_attributes);
                printf("%c     ",frascos[i][j]);
            }
            else
            {
                SetConsoleTextAttribute(hConsole, saved_attributes);
                printf("%c",frascos[i][j]);
            }
        }
        printf("\n");
    }

    //printf("\n10 Numeros aleatorios no intervalo [0, 99]: \n");
    //for(int i=1 ; i <= 10 ; i++){
     //   printf("Numero %d: %d\n",i, rand()%10); //estrategia para gerar numero num dado intervalo de interesse.
    //}
}
