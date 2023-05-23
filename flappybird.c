#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

HANDLE console;
COORD CursorPosition;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird[2][6] = { {'/','-','-','o','\\','\n'},
                    {'|','_','_','_',' ','>'} };
int birdPos = 6;
int score = 0;

void gotoxy(int x, int y){
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(int visible, DWORD size){
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder(){
	int i;
    for (i = 0; i < SCREEN_WIDTH; i++)
    {
        gotoxy(i, 0);
        printf("±");
        gotoxy(i, SCREEN_HEIGHT);
        printf("±");
    }

    for (i = 0; i < SCREEN_HEIGHT; i++)
    {
        gotoxy(0, i);
        printf("±");
        gotoxy(SCREEN_WIDTH, i);
        printf("±");
    }
    for (i = 0; i < SCREEN_HEIGHT; i++)
    {
        gotoxy(WIN_WIDTH, i);
        printf("±");
    }
}

void genPipe(int ind){
    gapPos[ind] = 3 + rand() % 14;
}

void drawPipe(int ind){
	int i;
    if (pipeFlag[ind] == 1)
    {
        for (i = 0; i < gapPos[ind]; i++)
        {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
            printf("***");
        }
        for (i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++)
        {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
            printf("***");
        }
    }
}

void erasePipe(int ind){
	int i;
    if (pipeFlag[ind] == 1){
        for (i = 0; i < gapPos[ind]; i++){
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
            printf("   ");
        }
        for (i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++){
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
            printf("   ");
        }
    }
}

void drawBird(){
	int i, j;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 6; j++)
        {
            gotoxy(j + 2, i + birdPos);
            printf("%c", bird[i][j]);
        }
    }
}

void eraseBird(){
	int i, j;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 6; j++)
        {
            gotoxy(j + 2, i + birdPos);
            printf(" ");
        }
    }
}

int collision(){
    if (pipePos[0] >= 61){
        if (birdPos < gapPos[0] || birdPos > gapPos[0] + GAP_SIZE){
            return 1;
        }
    }
    return 0;
}

void gameover(){
    system("cls");
    printf("\n");
    printf("\t\t--------------------------\n");
    printf("\t\t-------- Game Over -------\n");
    printf("\t\t--------------------------\n\n");
    printf("\t\tPress any key to go back to menu.");
    getch();
}

void updateScore(){
    gotoxy(WIN_WIDTH + 7, 5);
    printf("Score: %d\n", score);
}

void instructions(){
    system("cls");
    printf("Instructions");
    printf("\n----------------");
    printf("\nPress spacebar to make bird fly");
    printf("\nAvoid the buildings");
    printf("\n\nPress any key to go back to menu");
    getch();
}

void playGame(){
    birdPos = 6;
    score = 0;
    pipeFlag[0] = 1;
    pipeFlag[1] = 0;
    pipePos[0] = pipePos[1] = 4;

    system("cls");
    drawBorder();
    genPipe(0);
    updateScore();

    gotoxy(WIN_WIDTH + 5, 2);
    printf("FLAPPY BIRD");
    gotoxy(WIN_WIDTH + 6, 4);
    printf("----------");
    gotoxy(WIN_WIDTH + 6, 6);
    printf("----------");
    gotoxy(WIN_WIDTH + 7, 12);
    printf("Control ");
    gotoxy(WIN_WIDTH + 7, 13);
    printf("-------- ");
    gotoxy(WIN_WIDTH + 2, 14);
    printf(" Spacebar = jump");

    gotoxy(10, 5);
    printf("Press any key to start");
    getch();
    gotoxy(10, 5);
    printf("                      ");

    while (1)
    {

        if (kbhit())
        {
            char ch = getch();
            if (ch == 32)
            {
                if (birdPos > 3)
                    birdPos -= 3;
            }
            if (ch == 27)
            {
                break;
            }
        }

        drawBird();
        drawPipe(0);
        drawPipe(1);
        if (collision() == 1)
        {
            gameover();
            return;
        }
        Sleep(100);
        eraseBird();
        erasePipe(0);
        erasePipe(1);
        birdPos += 1;

        if (birdPos > SCREEN_HEIGHT - 2)
        {
            gameover();
            return;
        }

        if (pipeFlag[0] == 1)
            pipePos[0] += 2;

        if (pipeFlag[1] == 1)
            pipePos[1] += 2;

        if (pipePos[0] >= 40 && pipePos[0] < 42)
        {
            pipeFlag[1] = 1;
            pipePos[1] = 4;
            genPipe(1);
        }
        if (pipePos[0] > 68)
        {
            score++;
            updateScore();
            pipeFlag[1] = 0;
            pipePos[0] = pipePos[1];
            gapPos[0] = gapPos[1];
        }
    }
}

int main(){
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    setcursor(0, 0);
    srand((unsigned)time(NULL));

    do{
        system("cls");
        gotoxy(10, 5);
        printf(" -------------------------- ");
        gotoxy(10, 6);
        printf(" |      Flappy Bird       | ");
        gotoxy(10, 7);
        printf(" --------------------------");
        gotoxy(10, 9);
        printf("1. Start Game");
        gotoxy(10, 10);
        printf("2. Instructions");
        gotoxy(10, 11);
        printf("3. Quit");
        gotoxy(10, 13);
        printf("Select option: ");
        char op = getch();

        if (op == '1')
            playGame();
        else if (op == '2')
            instructions();
        else if (op == '3')
            exit(0);

    } while (1);

    return 0;
}