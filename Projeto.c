#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include <ctype.h>

#define AGUA '~'
#define ERRO 'X'
#define teste 'L'
#define NAVIO 'N'
#define ACERTO 'O'
#define HIDROAVIAO 'H'
#define PORTAAVIAO 'P'

int linha, coluna, i, j;
int TAMANHO = 0;
char arena[15][15], arena_inimigo[15][15], arena_inimigo_blank[15][15];
bool vezplayer = false;
bool vezbot = false;
int pontos = 0;
int acerto = 0;
bool endgame = false;
int life = 3;

void mapa()
{
    bool ctrl = false;

    do
    {
        printf("Escolha o tamanho do mapa");
        printf(" [10x10] ou [15x15]: ");
        scanf("%d%*c", &TAMANHO);

        if (TAMANHO != 15 && TAMANHO != 10)
        {
            ctrl = true;
            system("cls");
            printf("Tamanho Inválido!\n\n");
        }

        else

        {
            ctrl = false;
        }

    } while (ctrl == true);
}

// Dados das embarcações do jogador
struct embarcacoes
{
    int navio;
    int hidro_aviao;
    int porta_aviao;
};

typedef struct embarcacoes barcos;

barcos qt_barcos = {2, 2, 1};

int vida_inimiga = 12;

void menu() // Exibe menu principal do jogo
{

    char opcao = NULL;
    endgame = false;

    printf("\t\t\t                                 |__                                                          \n");
    Beep(50, 250);
    printf("\t\t\t                                 |\/                                                          \n");
    Beep(290, 250);
    printf("\t\t\t                                 ---                                                          \n");
    Beep(50, 250);
    printf("\t\t\t                                 / | [                                                        \n");
    Beep(50, 250);
    printf("\t\t\t                          !      | |||                                                        \n");
    Beep(349, 250);
    printf("\t\t\t                        _/|     _/|-++'                                                       \n");
    Beep(349, 250);
    printf("\t\t\t                    +  +--|    |--|--|_ |-                                                    \n");
    Beep(440, 250);
    printf("\t\t\t                 { /|__|  |/\__|  |--- |||__/                                                 \n");
    Beep(329, 250);
    printf("\t\t\t                +---------------___[}-_===_.'____                                           \n");
    Beep(50, 250);
    printf("\t\t\t                ____`-' ||___-{]_| _[}-  |     |_[___\==--               _                      \n");
    Beep(290, 250);
    printf("\t\t\t __..._____--==/___]_|__|_____________________________[___\==--____,------' .7                    \n");
    Beep(50, 250);
    printf("\t\t\t|                                                                     BB-61/                      \n");
    Beep(50, 250);
    printf("\t\t\t \_________________________________________________________________________|                      \n");
    Beep(349, 250);

    printf("\t\t\t\t\t-------------------------------------------\n");
    Beep(349, 250);
    printf("\t\t\t\t\t|                                         |\n");
    Beep(440, 250);
    printf("\t\t\t\t\t|                                         |\n");
    Beep(329, 250);
    printf("\t\t\t\t\t|             BATALHA NAVAL               |\n");
    Beep(50, 250);
    printf("\t\t\t\t\t|                                         |\n");
    Beep(290, 250);
    printf("\t\t\t\t\t|                                         |\n");
    Beep(50, 250);
    printf("\t\t\t\t\t|                                         |\n");
    Beep(50, 250);
    printf("\t\t\t\t\t|              1 - JOGAR                  |\n");
    Beep(349, 250);
    printf("\t\t\t\t\t|              2 - PLACAR                 |\n");
    Beep(349, 250);
    printf("\t\t\t\t\t|              3 - SAIR                   |\n");
    Beep(440, 250);
    printf("\t\t\t\t\t|              4 - GRUPO                  |\n");
    Beep(329, 250);
    printf("\t\t\t\t\t|                                         |\n");
    printf("\t\t\t\t\t|                                         |\n");
    printf("\t\t\t\t\t-------------------------------------------\n");

    opcao = getch();

    switch (opcao)
    {
    case '1':
        system("cls");
        mapa();
        break;

    case '3':
        exit(1);

    case '2':
        ranking();
        break;

    case '4':
        grupo();
        break;

    default:
        system("cls");
        menu();
        break;
    }
}

void grupo()
{
    char escolha;

    system("cls");

    printf("\n\t\t\t\t\t            DEVELOPERS                   \n");

    printf("\n\t\t\t\t\tDiego Jose Campos Silveira");

    printf("\n\t\t\t\t\tRaphael Murilo Gianei Claudino ");

    printf("\n\t\t\t\t\tThalissa Visentim Lopes");

    printf("\n\n\t\t\t\t\t[1]Ranking [2]Menu [3]Sair");
    escolha = getch();

    switch (escolha)
    {
    case '1':
        ranking();
        system("cls");
        menu();
        break;

    case '2':
        system("cls");
        menu();
        break;

    case '3':
        exit(1);

    default:
        system("cls");
        menu();
        break;
    }
}

void posicaomanualnavio()
{
    int l, c, direcao;
    char direcaoc[2];
    qt_barcos.navio = 2;
    bool ctrl = false;

    do
    {
        direcao = 0;
        do
        {
            printf("Digite a posição que deseja colocar [H]-Horizontal [V]-Vertical: ");
            fgets(direcaoc, 2, stdin);
            fflush(stdin);

            if (strcasecmp(direcaoc, "V") != 0 && strcasecmp(direcaoc, "H") != 0)
            {
                ctrl = true;
                system("cls");
                imprimeTabuleiro();
                printf("Posição Inválida\n");
            }
            else
            {
                ctrl = false;
            }

        } while (ctrl != false);
        do
        {
            do
            {
                printf("Digite a Linha que deseja jogar: ");
                scanf("%d%*c", &l);

                --l;

                if (l > TAMANHO || l < 0 || isdigit(l) != 0)
                {
                    fflush(stdin);
                    ctrl = true;
                    system("cls");
                    imprimeTabuleiro();
                    printf("Coordenada Inválida\n");
                }
                else
                {
                    ctrl = false;
                }
            } while (ctrl != false);

            do
            {
                printf("Digite a Coluna que deseja jogar: ");
                scanf("%d%*c", &c);

                --c;

                if (c > TAMANHO || c < 0 || isdigit(c) != 0)
                {
                    fflush(stdin);
                    ctrl = true;
                    system("cls");
                    imprimeTabuleiro();
                    printf("Coordenada Inválida\n");
                }
                else
                {
                    ctrl = false;
                }

            } while (ctrl != false);

            if (arena[l][c] != AGUA)
            {
                system("cls");
                imprimeTabuleiro();
                printf("Espaço ja preenchido\n");
                ctrl = true;
            }
            else
            {
                ctrl = false;
            }
        } while (ctrl != false);

        if (strcasecmp(direcaoc, "V") != 0)
        {
            direcao = 0;
        }

        if (strcasecmp(direcaoc, "H") == 0)
        {
            direcao = 3;
        }

        if (direcao == 0)
        {
            if (l == TAMANHO || l > TAMANHO - 3)
            {
                if (arena[l][c] == AGUA && arena[l - 1][c] == AGUA)
                    for (i = l; i < l + 3; i++)
                    {
                        arena[i - 2][c] = NAVIO;
                    }
                qt_barcos.navio--;
            }
            else
            {
                if (arena[l][c] == AGUA && arena[l + 1][c] == AGUA)
                    for (i = l; i < l + 3; i++)
                    {
                        arena[i][c] = NAVIO;
                    }
                qt_barcos.navio--;
            }
        }
        else
        {
            if (c == TAMANHO || c > TAMANHO - 3)
            {
                if (arena[l][c] == AGUA && arena[l][c - 1] == AGUA)
                    for (i = c; i < c + 3; i++)
                    {
                        arena[l][i - 2] = NAVIO;
                    }
                qt_barcos.navio--;
            }
            else
            {
                if (arena[l][c] == AGUA && arena[l][c + 1] == AGUA)
                    for (i = c; i < c + 3; i++)
                    {
                        arena[l][i] = NAVIO;
                    }
                qt_barcos.navio--;
            }
        }
        imprimeTabuleiro();
    } while (qt_barcos.navio != 0);

    imprimeTabuleiro();
}

void posicaomanualportaaviao()
{
    int l, c, direcao;
    char direcaoc[2];
    qt_barcos.porta_aviao = 1;
    bool ctrl = false;

    do
    {
        direcao = 0;
        do
        {
            printf("Digite a posição que deseja colocar [H]-Horizontal [V]-Vertical: ");
            fgets(direcaoc, 2, stdin);
            fflush(stdin);

            if (strcasecmp(direcaoc, "V") != 0 && strcasecmp(direcaoc, "H") != 0)
            {
                ctrl = true;
                system("cls");
                imprimeTabuleiro();
                printf("Posição Invalida\n");
            }
            else
            {
                ctrl = false;
            }

        } while (ctrl != false);
        do
        {
            do
            {
                printf("Digite a Linha que deseja jogar: ");
                scanf("%d%*c", &l);

                --l;

                if (l > TAMANHO || l < 0 || isdigit(l) != 0)
                {
                    fflush(stdin);
                    ctrl = true;
                    system("cls");
                    imprimeTabuleiro();
                    printf("Coordenada Inválida\n");
                }
                else
                {
                    ctrl = false;
                }
            } while (ctrl != false);

            do
            {
                printf("Digite a Coluna que deseja jogar: ");
                scanf("%d%*c", &c);

                --c;

                if (c > TAMANHO || c < 0 || isdigit(c) != 0)
                {
                    fflush(stdin);
                    ctrl = true;
                    system("cls");
                    imprimeTabuleiro();
                    printf("Coordenada Inválida\n");
                }
                else
                {
                    ctrl = false;
                }

            } while (ctrl != false);

            if (arena[l][c] != AGUA)
            {
                system("cls");
                imprimeTabuleiro();
                printf("Espaço já preenchido\n");
                ctrl = true;
            }
            else
            {
                ctrl = false;
            }
        } while (ctrl != false);

        if (strcasecmp(direcaoc, "V") == 0)
        {
            direcao = 0;
        }
        else
        {
            direcao = 3;
        }

        if (direcao == 0)
        {
            if ((l == TAMANHO || l > TAMANHO - 4))
            {
                if (arena[l][c] == AGUA && arena[l - 1][c] == AGUA &&
                    arena[l - 2][c] == AGUA && arena[l - 3][c] == AGUA)
                {
                    for (i = l; i < l + 4; i++)
                    {
                        arena[i - 3][c] = PORTAAVIAO;
                    }
                    qt_barcos.porta_aviao--;
                }
            }
            else
            {
                if (arena[l][c] == AGUA && arena[l + 1][c] == AGUA &&
                    arena[l + 2][c] == AGUA && arena[l + 3][c] == AGUA)
                    for (i = l; i < l + 4; i++)
                    {
                        arena[i][c] = PORTAAVIAO;
                    }
                qt_barcos.porta_aviao--;
            }
        }
        else
        {
            if (c == TAMANHO || c > TAMANHO - 4)
            {
                if (arena[l][c] == AGUA && arena[l][c - 1] == AGUA &&
                    arena[l][c - 2] == AGUA && arena[l][c - 3] == AGUA)
                {
                    for (i = c; i < c + 4; i++)
                    {
                        arena[l][i - 3] = PORTAAVIAO;
                    }
                    qt_barcos.porta_aviao--;
                }
            }
            else
            {
                if (arena[l][c] == AGUA && arena[l][c + 1] == AGUA &&
                    arena[l][c + 2] == AGUA && arena[l][c + 3] == AGUA)
                {
                    for (i = c; i < c + 4; i++)
                    {
                        arena[l][i] = PORTAAVIAO;
                    }
                    qt_barcos.porta_aviao--;
                }
            }
        }
        imprimeTabuleiro();
    } while (qt_barcos.porta_aviao != 0);

    imprimeTabuleiro();
}

void picaomanualhidro()
{
    int l, c, direcao;
    char direcaoc[2], posicao[2];
    qt_barcos.hidro_aviao = 2;
    bool ctrl = false;

    do
    {
        direcao = 0;
        do
        {
            printf("Digite a posição que deseja colocar [H]-Horizontal [V]-Vertical: ");
            fgets(direcaoc, 2, stdin);
            fflush(stdin);

            if (strcasecmp(direcaoc, "V") != 0 && strcasecmp(direcaoc, "H") != 0)
            {
                ctrl = true;
                system("cls");
                imprimeTabuleiro();
                printf("Posição Inválida\n");
            }
            else
            {
                ctrl = false;
            }

        } while (ctrl != false);
        do
        {
            do
            {
                printf("Digite a Linha que deseja jogar: ");
                scanf("%d%*c", &l);

                --l;

                if (l > TAMANHO || l < 0 || isdigit(l) != 0)
                {
                    fflush(stdin);
                    ctrl = true;
                    system("cls");
                    imprimeTabuleiro();
                    printf("Coordenada Inválida\n");
                }
                else
                {
                    ctrl = false;
                }
            } while (ctrl != false);

            do
            {
                printf("Digite a Coluna que deseja jogar: ");
                scanf("%d%*c", &c);

                --c;

                if (c > TAMANHO || c < 0 || isdigit(c) != 0)
                {
                    fflush(stdin);
                    ctrl = true;
                    system("cls");
                    imprimeTabuleiro();
                    printf("Coordenada Inválida\n");
                }
                else
                {
                    ctrl = false;
                }

            } while (ctrl != false);

            if (arena[l][c] != AGUA)
            {
                system("cls");
                imprimeTabuleiro();
                printf("Espaço ja preenchido\n");
                ctrl = true;
            }
            else
            {
                ctrl = false;
            }
        } while (ctrl != false);

        if (strcasecmp(direcaoc, "V") == 0)
        {
            direcao = 0;
            printf("Digite a direção que deseja colocar o Hidro Avião [E]-Esquerda [D]-Direita: ");
            fgets(posicao, 2, stdin);
            fflush(stdin);
        }
        else
        {
            direcao = 3;
            printf("Digite a direção que deseja colocar o Hidro Avião [C]-Cima [B]-Baixo: ");
            fgets(posicao, 2, stdin);
            fflush(stdin);
        }

        if (direcao == 3)
        {
            if (strcasecmp(posicao, "B") == 0)
            {
                // horizontal cabeça para baixo
                if (arena[l][c] == AGUA && arena[l + 1][c + 1] == AGUA && arena[l][c + 2] == AGUA)
                {
                    arena[l][c] = HIDROAVIAO;
                    arena[l + 1][c + 1] = HIDROAVIAO;
                    arena[l][c + 2] = HIDROAVIAO;
                    qt_barcos.hidro_aviao--;
                }
            }
            if (strcasecmp(posicao, "C") == 0)
            {
                // horizontal cabeça para cima
                if (arena[l][c] == AGUA && arena[l - 1][c + 1] == AGUA && arena[l][c + 2] == AGUA)
                {
                    arena[l][c] = HIDROAVIAO;
                    arena[l - 1][c + 1] = HIDROAVIAO;
                    arena[l][c + 2] = HIDROAVIAO;
                    qt_barcos.hidro_aviao--;
                }
            }
        }
        else
        {
            if (strcasecmp(posicao, "D") == 0)
            {
                // vertical cabeça para direita
                if (arena[l][c] == AGUA && arena[l + 1][c + 1] == AGUA && arena[l + 2][c] == AGUA)
                {
                    arena[l][c] = HIDROAVIAO;
                    arena[l + 1][c + 1] = HIDROAVIAO;
                    arena[l + 2][c] = HIDROAVIAO;
                    qt_barcos.hidro_aviao--;
                }
            }
            if (strcasecmp(posicao, "E") == 0)
            {
                // vertical cabeça para esquerda
                if (arena[l][c] == AGUA && arena[l + 1][c - 1] == AGUA && arena[l + 2][c] == AGUA)
                {
                    arena[l][c] = HIDROAVIAO;
                    arena[l + 1][c - 1] = HIDROAVIAO;
                    arena[l + 2][c] = HIDROAVIAO;
                    qt_barcos.hidro_aviao--;
                }
            }
        }
        imprimeTabuleiro();
    } while (qt_barcos.hidro_aviao != 0);

    imprimeTabuleiro();
}

void imprime_Navio()
{
    int l, c, direcao;
    bool ctrl = false;

    do
    {
        do
        {
            direcao = rand() % 3;
            l = rand() % TAMANHO;
            c = rand() % TAMANHO;

            if (arena[l][c] != AGUA)
            {
                system("cls");
                imprimeTabuleiro();
                ctrl = true;
            }
            else
            {
                ctrl = false;
            }

            if (l > TAMANHO || l < 0)
            {
                l = rand() % TAMANHO;
                c = rand() % TAMANHO;
                ctrl = true;
                system("cls");
                imprimeTabuleiro();
            }
            else
            {
                ctrl = false;
            }

            if (c > TAMANHO || c < 0)
            {
                l = rand() % TAMANHO;
                c = rand() % TAMANHO;
                ctrl = true;
                system("cls");
                imprimeTabuleiro();
            }
            else
            {
                ctrl = false;
            }
        } while (ctrl != false);

        if (direcao == 0)
        {
            if (l == TAMANHO || l > TAMANHO - 3)
            {
                if (arena_inimigo[l][c] == AGUA && arena_inimigo[l - 1][c] == AGUA)
                    for (i = l; i < l + 3; i++)
                    {
                        arena_inimigo[i - 3][c] = NAVIO;
                    }
                qt_barcos.navio--;
            }
            else
            {
                if (arena_inimigo[l][c] == AGUA && arena_inimigo[l + 1][c] == AGUA)
                    for (i = l; i < l + 3; i++)
                    {
                        arena_inimigo[i][c] = NAVIO;
                    }
                qt_barcos.navio--;
            }
        }
        else
        {
            if (c == TAMANHO || c > TAMANHO - 3)
            {
                if (arena_inimigo[l][c] == AGUA && arena_inimigo[l][c - 1] == AGUA)
                    for (i = c; i < c + 3; i++)
                    {
                        arena_inimigo[l][i - 3] = NAVIO;
                    }
                qt_barcos.navio--;
            }
            else
            {
                if (arena_inimigo[l][c] == AGUA && arena_inimigo[l][c + 1] == AGUA)
                    for (i = c; i < c + 3; i++)
                    {
                        arena_inimigo[l][i] = NAVIO;
                    }
                qt_barcos.navio--;
            }
        }

    } while (qt_barcos.navio != 0);
}

// Define e imprime Hidro-Avião
void imprime_hidroaviao()
{
    int l, c;
    bool ctrl = false;

    do
    {
        do
        {
            l = rand() % TAMANHO;
            c = rand() % TAMANHO;

            if (arena[l][c] != AGUA)
            {
                system("cls");
                imprimeTabuleiro();
                ctrl = true;
            }
            else
            {
                ctrl = false;
            }

            if (l > TAMANHO || l < 0)
            {
                l = rand() % TAMANHO;
                c = rand() % TAMANHO;
                ctrl = true;
                system("cls");
                imprimeTabuleiro();
            }
            else
            {
                ctrl = false;
            }

            if (c > TAMANHO || c < 0)
            {
                l = rand() % TAMANHO;
                c = rand() % TAMANHO;
                ctrl = true;
                system("cls");
                imprimeTabuleiro();
            }
            else
            {
                ctrl = false;
            }
        } while (ctrl != false);

        if (l == 0 && c == 0 && arena_inimigo[l][c] == AGUA &&
            arena_inimigo[l + 1][c + 1] == AGUA && arena_inimigo[l][c + 2] == AGUA)
        {
            arena_inimigo[l][c] = HIDROAVIAO;
            arena_inimigo[l + 1][c + 1] = HIDROAVIAO;
            arena_inimigo[l][c + 2] = HIDROAVIAO;
            qt_barcos.hidro_aviao--;
        }
        else if (l == 0 && c == TAMANHO && arena_inimigo[l][c] == AGUA &&
                 arena_inimigo[l - 1][c - 1] == AGUA && arena_inimigo[l - 1][c + 1] == AGUA)
        {
            arena_inimigo[l][c] = HIDROAVIAO;
            arena_inimigo[l - 1][c - 1] = HIDROAVIAO;
            arena_inimigo[l - 1][c + 1] = HIDROAVIAO;
            qt_barcos.hidro_aviao--;
        }
        else if (l == TAMANHO && c == 0 && arena_inimigo[l][c] == AGUA &&
                 arena_inimigo[l + 1][c - 1] == AGUA && arena_inimigo[l][c - 2] == AGUA)
        {
            arena_inimigo[l][c] = HIDROAVIAO;
            arena_inimigo[l + 1][c - 1] = HIDROAVIAO;
            arena_inimigo[l][c - 2] = HIDROAVIAO;
            qt_barcos.hidro_aviao--;
        }
        else if (l == TAMANHO && c == TAMANHO && arena_inimigo[l][c] == AGUA &&
                 arena_inimigo[l - 1][c - 1] == AGUA && arena_inimigo[l][c - 2] == AGUA)
        {
            arena_inimigo[l][c] = HIDROAVIAO;
            arena_inimigo[l - 1][c - 1] = HIDROAVIAO;
            arena_inimigo[l][c - 2] = HIDROAVIAO;
            qt_barcos.hidro_aviao--;
        }
        else if (l < TAMANHO && c <= TAMANHO - 2 &&
                 arena_inimigo[l][c] == AGUA && arena_inimigo[l + 1][c + 1] == AGUA && arena_inimigo[l][c + 2] == AGUA)
        {
            arena_inimigo[l][c] = HIDROAVIAO;
            arena_inimigo[l + 1][c + 1] = HIDROAVIAO;
            arena_inimigo[l][c + 2] = HIDROAVIAO;
            qt_barcos.hidro_aviao--;
        }
        else if (l > 0 && (c > 0 || c < TAMANHO) &&
                 arena_inimigo[l][c] == AGUA && arena_inimigo[l + 1][c - 1] == AGUA && arena_inimigo[l + 1][c + 1] == AGUA)
        {
            arena_inimigo[l][c] = HIDROAVIAO;
            arena_inimigo[l + 1][c - 1] = HIDROAVIAO;
            arena_inimigo[l + 1][c + 1] = HIDROAVIAO;
            qt_barcos.hidro_aviao--;
        }
        else if (l < TAMANHO - 2 && (c > 2 || c < TAMANHO - 8) &&
                 arena_inimigo[l][c] == AGUA && arena_inimigo[l + 1][c + 1] == AGUA && arena_inimigo[l + 2][c] == AGUA)
        {
            arena_inimigo[l][c] = HIDROAVIAO;
            arena_inimigo[l + 1][c + 1] = HIDROAVIAO;
            arena_inimigo[l + 2][c] = HIDROAVIAO;
            qt_barcos.hidro_aviao--;
        }
        else if (l < TAMANHO - 2 && c > 0 &&
                 arena_inimigo[l][c] == AGUA && arena_inimigo[l + 1][c - 1] == AGUA && arena_inimigo[l + 2][c] == AGUA)
        {
            arena_inimigo[l][c] = HIDROAVIAO;
            arena_inimigo[l + 1][c - 1] = HIDROAVIAO;
            arena_inimigo[l + 2][c] = HIDROAVIAO;
            qt_barcos.hidro_aviao--;
        }
    } while (qt_barcos.hidro_aviao != 0);
}

// Define e imprime Porta-Avião
void imprime_portaaviao()
{
    int l, c, direcao;
    bool ctrl = false;

    do
    {
        do
        {
            direcao = rand() % 2;
            l = rand() % TAMANHO;
            c = rand() % TAMANHO;

            if (arena[l][c] != AGUA)
            {
                system("cls");
                imprimeTabuleiro();
                ctrl = true;
            }
            else
            {
                ctrl = false;
            }

            if (l > TAMANHO || l < 0)
            {
                l = rand() % TAMANHO;
                c = rand() % TAMANHO;
                ctrl = true;
                system("cls");
                imprimeTabuleiro();
            }
            else
            {
                ctrl = false;
            }

            if (c > TAMANHO || c < 0)
            {
                l = rand() % TAMANHO;
                c = rand() % TAMANHO;
                ctrl = true;
                system("cls");
                imprimeTabuleiro();
            }
            else
            {
                ctrl = false;
            }
        } while (ctrl != false);

        if (direcao == 0)
        {
            if ((l == TAMANHO || l > TAMANHO - 4))
            {
                if (arena_inimigo[l][c] == AGUA && arena_inimigo[l - 1][c] == AGUA &&
                    arena_inimigo[l - 2][c] == AGUA && arena_inimigo[l - 3][c] == AGUA)
                {
                    for (i = l; i < l + 4; i++)
                    {
                        arena_inimigo[i - 4][c] = PORTAAVIAO;
                    }
                    qt_barcos.porta_aviao--;
                }
            }
            else
            {
                if (arena_inimigo[l][c] == AGUA && arena_inimigo[l + 1][c] == AGUA &&
                    arena_inimigo[l + 2][c] == AGUA && arena_inimigo[l + 3][c] == AGUA)
                    for (i = l; i < l + 4; i++)
                    {
                        arena_inimigo[i][c] = PORTAAVIAO;
                    }
                qt_barcos.porta_aviao--;
            }
        }
        else
        {
            if (c == TAMANHO || c > TAMANHO - 4)
            {
                if (arena_inimigo[l][c] == AGUA && arena_inimigo[l][c - 1] == AGUA &&
                    arena_inimigo[l][c - 2] == AGUA && arena_inimigo[l][c - 3] == AGUA)
                {
                    for (i = c; i < c + 4; i++)
                    {
                        arena_inimigo[l][i - 4] = PORTAAVIAO;
                    }
                    qt_barcos.porta_aviao--;
                }
            }
            else
            {
                if (arena_inimigo[l][c] == AGUA && arena_inimigo[l][c + 1] == AGUA &&
                    arena_inimigo[l][c + 2] == AGUA && arena_inimigo[l][c + 3] == AGUA)
                {
                    for (i = c; i < c + 4; i++)
                    {
                        arena_inimigo[l][i] = PORTAAVIAO;
                    }
                    qt_barcos.porta_aviao--;
                }
            }
        }
    } while (qt_barcos.porta_aviao != 0);
}

// Prepara Tabuleiro
void prepara_tabuleiro()
{
    int l, c;

    for (l = 0; l < TAMANHO; l++)
    {
        for (c = 0; c < TAMANHO; c++)
        {
            if (arena[l][c] == '\0' && arena_inimigo[l][c] == '\0')
            {
                arena_inimigo[l][c] = AGUA;
                arena_inimigo_blank[l][c] = AGUA;
                arena[l][c] = AGUA;
            }
        }
    }
}

// Imprime tabuleiro
void imprimeTabuleiro()
{
    int l, c;

    system("cls");

    // imprime testo e numeros em cima dos mapas
    if (TAMANHO == 10)
    {
        // sublinhado
        for (c = 0; c < TAMANHO * 6 + 2; c++)
        {
            printf("%c", 95);
        }

        printf("\n");

        printf("\t     Player \t\t\t         IA   \n");

        for (c = 0; c < TAMANHO * 6 + 2; c++)
        {
            printf("%c", 175);
        }
    }

    else
    {

        // sublinhado
        for (c = 0; c < TAMANHO * 6 - 8; c++)
        {
            printf("%c", 95);
        }

        printf("\n");

        printf("\t          Player \t\t\t\t         IA\n");

        for (c = 0; c < TAMANHO * 5 + 7; c++)
        {
            printf("%c", 175);
        }
    }

    printf("\n");

    for (l = 0; l < TAMANHO; l++)
    {
        printf(" %02d | ", l + 1);

        for (c = 0; c < TAMANHO; c++)
        {
            printf(" %c", arena[l][c]);
        }
        printf("    |    ");
        printf(" %02d | ", l + 1);
        for (c = 0; c < TAMANHO; c++)
            printf(" %c", arena_inimigo_blank[l][c]);
        printf("\n");
    }

    if (TAMANHO == 10)
    {
        printf("       ");

        for (c = 0; c < TAMANHO; c++)
        {
            printf("%d ", c + 1);
        }

        printf("\t\t  ");

        for (c = 0; c < TAMANHO; c++)
        {
            printf("%d ", c + 1);
        }
    }

    printf("\n");

    // Exibe principais informações na tela
    printf("\nVida Inimiga: %d/3\n\n", life);
}

// Controles do jogador
int controles()
{

    int l, c;
    vezplayer = true;
    bool ctrl = false;

    do
    {
        do
        {
            ctrl = false;
            if (vezplayer == true)
            {
                printf("Informe a linha que deseja atirar: ");
                scanf("%i", &l);
                printf("Informe a coluna que deseja atirar: ");
                scanf("%i", &c);
                printf("\n");
                fflush(stdin);
                l--;
                c--;
            }

            if (arena_inimigo_blank[l][c] == ERRO)
            {
                system("cls");
                imprimeTabuleiro();
                printf("Este espaço já está preenchido\n");
                ctrl = true;
            }

            if (arena_inimigo_blank[l][c] == ACERTO)
            {
                system("cls");
                imprimeTabuleiro();
                printf("Este espaço já está preenchido\n");
                ctrl = true;
            }
            if (isdigit(l) != 0 || isdigit(c) != 0)
            {
                fflush(stdin);
                system("cls");
                imprimeTabuleiro();
                printf("Caractere Invalido\n");
                ctrl = true;
            }
        } while (ctrl == true);

        if (l >= 0 && l < TAMANHO && c >= 0 && c < TAMANHO && vezplayer == true)
        {
            switch (arena_inimigo[l][c])
            {
            case AGUA:
                arena_inimigo_blank[l][c] = ERRO;
                system("cls");
                imprimeTabuleiro();
                printf("Errou!...    \n");
                IA();
                break;

            case HIDROAVIAO:
                arena_inimigo_blank[l][c] = ACERTO;
                system("cls");
                imprimeTabuleiro();
                printf("Acertou...\n");
                vida_inimiga--;
                if (vida_inimiga == 9 || vida_inimiga == 6 || vida_inimiga == 3)
                {
                    life--;
                }
                pontos = pontos + 150;
                break;

            case NAVIO:
                arena_inimigo_blank[l][c] = ACERTO;
                system("cls");
                imprimeTabuleiro();
                printf("Acertou...\n");
                vida_inimiga--;
                if (vida_inimiga == 9 || vida_inimiga == 6 || vida_inimiga == 3)
                {
                    life--;
                }
                pontos = pontos + 50;
                break;

            case PORTAAVIAO:
                arena_inimigo_blank[l][c] = ACERTO;
                system("cls");
                imprimeTabuleiro();
                printf("Acertou...\n");
                vida_inimiga--;
                if (vida_inimiga == 9 || vida_inimiga == 6 || vida_inimiga == 3)
                {
                    life--;
                }
                pontos = pontos + 300;
                break;

            default:
                printf("Errou!\n");
            }
        }

        else
        {
            system("cls");
            imprimeTabuleiro();
            printf("Coordenadas inválidas\n");
        }

        if (life == 0)
        {
            system("cls");
            life = 0;
            imprimeTabuleiro();
            printf("\t\t\t    FIM DE JOGO\n");
            printf("\t\t\t    VOCÊ VENCEU!\n");
            system("PAUSE");
            endgame = true;
            ranking();
        }

        if (acerto == 12)
        {
            printf("\t\t\t    FIM DE JOGO\n");
            printf("\t\t\t    VOCÊ PERDEU\n");
            system("PAUSE");
            imprimeTabuleiro();
            endgame = true;
            ranking();
        }
    } while (vida_inimiga != 0 && acerto != 12 && endgame == false);
}

void randvez()
{
    int vez;

    vez = rand() % 1;

    if (vez == 1)
    {
        vezplayer = true;
        vezbot = false;
        controles();
    }
    else
    {
        vezplayer = false;
        vezbot = true;
        IA();
    }
}

// BOT
int IA()
{
    int l, c, l1[2], c1[2], r1, r2;
    vezbot = true;
    imprimeTabuleiro();

    do
    {
        // randomiza onde atirar no mapa
        l = rand() % TAMANHO;
        c = rand() % TAMANHO;

        if (vezbot == true)
        {
            do
            {
                if (arena[l][c] == ERRO)
                {
                    l = rand() % TAMANHO;
                    c = rand() % TAMANHO;
                }
            } while (arena[l][c] == ERRO);

            // verifica se acertou um navio
            if (arena[l][c] != AGUA && arena[l][c] != ERRO && arena[l][c] != ACERTO)
            {
                arena[l][c] = ACERTO;
                vezbot = true;      // define a vez do bot como sendo verdadeira
                imprimeTabuleiro(); // atualiza tabuleiro
                acerto++;
            }

            // troca o simbolo de agua por erro caso erre o navio
            if (arena[l][c] == AGUA)
            {
                arena[l][c] = ERRO;
                vezbot = false;
                imprimeTabuleiro();
            }

            // caso acerte o navio randomiza uma posição para tentar acertar outro em uma are de 7x7
            if (arena[l][c] == ACERTO && vezbot == true)
            {
                l1[1] = rand() % 7 - 3;
                c1[1] = rand() % 7 - 3;

                // impede que o bot jogue fora da area maxima do mapa
                do
                {
                    if (l <= 0 || l >= TAMANHO || r1 <= 0 || r1 >= TAMANHO)
                    {
                        l1[1] = rand() % 7 - 3; // randomiza entre -3 e 3
                        r1 = l - l1[1];
                    }
                    else
                    {
                        r1 = l - l1[1];
                    }
                } while (r1 < 0 || r1 > TAMANHO);

                do
                {
                    if (c <= 0 || c >= TAMANHO || r2 <= 0 || r2 >= TAMANHO)
                    {
                        c1[1] = rand() % 7 - 3;
                        r2 = c - c1[1];
                    }
                    else
                    {
                        r2 = c - c1[1];
                    }

                } while (r2 < 0 || r2 > TAMANHO);

                // troca o simbolo do navio para acerto
                if (arena[l][c] != AGUA && arena[l][c] != ERRO && arena[l][c] != ACERTO)
                {
                    arena[r1][r2] = ACERTO;
                    imprimeTabuleiro();
                }
            }

            // define que a vez do bot acabou caso erre um navio, caso contrario repete o codigo
            if (arena[l][c] == AGUA)
            {
                vezbot = false;
                vezplayer = true;
                controles();
            }
        }
    } while (vezbot != false);
    imprimeTabuleiro();
}

void ranking()
{

    int x;
    char nome[4], placar, escolha;

    FILE *pont_arq;

    system("cls");
    printf("\n\t\t\t\t\t     ######- Ranking de Jogadores -######\n");
    printf("  \n");
    printf("\t\t\t\t\t\t\tPONTOS - NOME \n");
    printf("  \n");

    // abrindo o arquivo_frase em modo "leitura e escrita"
    pont_arq = fopen("ranking.txt", "a+");

    if (pont_arq == NULL)
    {
        printf("Erro de Abertura do arquivo");
        system("PAUSE");
        exit(1);
    }

    fflush(stdin);

    if (endgame == true)
    {
        printf("\t\t\t\t\t\t  %d ................. ", pontos);
        fgets(nome, 4, stdin);

        printf("\t\t\t\t\t\t       Digite 3 siglas\n");

        fprintf(pont_arq, "\t\t\t\t\t\t  %d ................. %s", pontos, nome);
        fprintf(pont_arq, "\n");

        printf("\n\t\t\t\t\t[1]Apagar [2]Menu [3]Jogar Novamente [4]Sair");
        escolha = getch();

        escolha = getch();

        switch (escolha)
        {
        case '1':
            fclose(pont_arq);
            remove("ranking.txt");
            system("cls");
            menu();
            break;

        case '2':
            system("cls");
            fclose(pont_arq);
            menu();
            break;

        case '3':
            system("cls");
            fclose(pont_arq);
            menu();

        case '4':
            fclose(pont_arq);
            exit(1);

        default:
            system("cls");
            fclose(pont_arq);
            menu();
            break;
        }
    }

    else
    {
        while ((placar = fgetc(pont_arq)) != EOF)
        {
            printf("%c", placar);
        }
        printf("\n\t\t\t\t\t\t  [1]Apagar [2]Menu [3]Sair");
        escolha = getch();

        switch (escolha)
        {
        case '1':
            fclose(pont_arq);
            remove("ranking.txt");
            system("cls");
            menu();
            break;

        case '2':
            system("cls");
            fclose(pont_arq);
            main();
            break;

        case '3':
            system("cls");
            fclose(pont_arq);
            exit(1);

        default:
            system("cls");
            fclose(pont_arq);
            menu();
            break;
        }
    }

    fclose(pont_arq);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    srand((unsigned)time(NULL));
    menu();
    prepara_tabuleiro();
    imprime_Navio();
    imprime_hidroaviao();
    imprime_portaaviao();
    imprimeTabuleiro();
    printf("Derrube 3 Navios para Vencer\n");
    posicaomanualnavio();
    picaomanualhidro();
    posicaomanualportaaviao();
    randvez();
    controles();
    return 0;
}
