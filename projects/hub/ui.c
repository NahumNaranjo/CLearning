#include "ui.h"
#include <string.h>

char gamesUI(){
    MenuOption options[] = {
        {"No games yet", "1"},
        {"Main menu", "e"}
    };
    size_t count;
    Menu* menu = createMenu("Built-in Games", options, count);
    displayTitle(menu->title);
    char result = *displayMenu(menu);
    return result;
}

char toolsUI(){
    MenuOption options[] = {
        {"CXT", "x"},
        {"Main menu", "e"}
    };
    size_t count;
    Menu* menu = createMenu("Clearning Executable Tools", options, count);
    displayTitle(menu->title);
    char result = *displayMenu(menu);
    return result;
}

char mainMenu(){
    MenuOption options[] = {
        {"Games", "g"},
        {"Tools", "t"},
        {"Exit", "e"}
    };
    size_t count;
    Menu* menu = createMenu("CLearning HUB", options, count);
    displayTitle(menu->title);
    char result = *displayMenu(menu);
    return result;
}