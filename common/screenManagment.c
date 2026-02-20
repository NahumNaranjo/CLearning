#include "screenManagment.h"

// Clears console
void clearConsole(){
    system("cls");
}

// stops the process until the user presses enter
void Stop(){
    printf("Press enter to continue...\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//stops the process until the user presses enter and displays a custom message
void StopM(char* msg){
    printf("%s\n", msg);
    printf("Press enter to continue...\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}