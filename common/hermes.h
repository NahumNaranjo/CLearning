#ifndef HERMES_H
#define HERMES_H
    #include <stdio.h>
    #include <stdlib.h>
    // Clears console
    static inline void clearConsole(void){
        #if defined(_WIN32) || defined(_WIN64)
            system("cls");
        #elif defined(__linux__) || defined(__APPLE__)
            system("clear");
        #endif
    }

    //clears console and shows a message
    static inline void clearConsoleM(const char* message){
        #if defined(_WIN32) || defined(_WIN64)
            system("cls");
        #elif defined(__linux__) || defined(__APPLE__)
            system("clear");
        #endif
        printf("%s\n", message);
    }

    //Waits for the user to press enter and clears
    static inline void clearUntil(void){
        printf("Press enter to continue...\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        #if defined(_WIN32) || defined(_WIN64)
            system("cls");
        #elif defined(__linux__) || defined(__APPLE__)
            system("clear");
        #endif
    }


    // stops the process until the user presses enter
    static inline void Stop(void){
        printf("Press enter to continue...\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // stops the process until the user presses enter and displays a custom message
    static inline void StopM(const char* msg){
        printf("%s\n", msg);
        printf("Press enter to continue...\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // Reads line
    static inline char* readLine(){
        char returning[256];
        fgets(returning, 0, stdin);
        return returning;
    }

#endif