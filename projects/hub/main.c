#include "ui.h"
#include "hub.h"
#include <hermes.h>

int main(){
    char res;
    while(1){
        res = mainMenu();
        if(res == 'g'){
            while(1){
                res = gamesUI();
                if(res = 'e'){
                    break;
                }
                gamesInterpreter(&res);
                clearConsole();
            }
        }
        if(res == 't'){
            while(1){
                res = toolsUI();
                if(res = 'e'){
                    break;
                }
                toolsInterpreter(&res);
                clearConsole(); 
            }
        }
        clearConsole();
        if(res == 'e') return 0;
    }
    return 0;
}