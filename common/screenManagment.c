#include "screenManagment.h"

void clearConsole(){
    system("cls");
}

void Stop(){
    printf("Press enter to continue...\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void StopM(char* msg){
    printf("%s\n", msg);
    printf("Press enter to continue...\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}