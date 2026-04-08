#include "dialog.h"

void dialogSequence(dialog* dialogs){
    for(int i = 0; dialogs[i].name; i++){
        printf("%s: %s\n", dialogs[i].name, dialogs[i].text);
    }
    
}