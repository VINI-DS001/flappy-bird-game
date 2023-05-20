#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char bird[2][6] = { {'/','-','-','o','\\','\n'}, {'|','_','_','_',' ','>'} };


void drawBird(){
    int i, j;
    for (i = 0; i < 2; i++){
        for (j = 0; j < 6; j++){
            printf("%c", bird[i][j]);
        }
    }
}

void play()
{

    system("cls");
    
    drawBird();
    
}


void instructions(){
    system("cls");
    printf("Instructions: \n");
    printf("\n1. Press spacebar to make bird fly");
    printf("\n2. Avoid the buildings\n");
    printf("\nPress any key to go back to menu");
    getch();
}

int main(){
	srand((unsigned)time(NULL));

    
        system("cls");
        printf(" -------------------------- \n");
        printf(" |*******Flappy Bird******| \n");
        printf(" --------------------------\n");
        printf("1. Play Game\n");
        printf("2. Instructions\n");
        printf("3. Exit\n");
        printf("Select an option: ");
        char op = getche();
        
		if(op == '1'){
			play();
		}
        else if(op == '2'){
        	instructions();
		}
        else if(op == '3')exit(0);


    return 0;
}