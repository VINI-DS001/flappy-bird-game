#include<stdio.h>
#include<stdlib.h>

void instructions(){
    system("cls");
    printf("Instructions: \n");
    printf("\n1. Press spacebar to make bird fly");
    printf("\n2. Avoid the buildings\n");
    printf("\nPress any key to go back to menu");
    getch();
}

int main(){

    do{
        system("cls");
        printf(" -------------------------- \n");
        printf(" |*******Flappy Bird******| \n");
        printf(" --------------------------\n");
        printf("1. Play Game\n");
        printf("2. Instructions\n");
        printf("3. Exit\n");
        printf("Select an option: ");
        char op = getche();

        if (op == '2'){
        	instructions();
		}
        else if(op == '3')exit(0);

    } while (1);

    return 0;
}