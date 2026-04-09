#include "dialog.h"

// Print a decision sequence
void printDecision(dialog dec){
    printf("%s\n", dec.decisionText);
    for(int j = 0; j < (sizeof(dec.decisionOptions) / sizeof(dec.decisionOptions[0])); j++){
        printf("%d: %s\n", j, dec.decisionOptions[j]);
    }
}

// automatically processes all dialogs
void dialogSequence(dialog* dialogs){

    int scriptProgress = atoi(getenv("SCRIPT_PROGRESS"));
    if(scriptProgress){
        perror("scriptProgress is not aviable in env, the program might have behavioral issues");
    }

    for(int i = 0; i < (sizeof(dialogs[i]) / sizeof(dialog)); i++){
        if(dialogs[i].type == 's'){ // sequence
            printf("%s: %s\n", dialogs[i].name, dialogs[i].text);
            Stop();
        } else if (dialogs[i].type == 'd'){ // decision
            // Print
            printDecision(dialogs[i]);
            // get choice
            int choice;
            short correct = 0;
            scanf("%d", &choice);

            // error handling
            do
            {
                for(int j = 0; j < (sizeof(dialogs[i].decisionOptions) / sizeof(dialogs[i].decisionOptions[0])); j++){
                    if(j == choice){
                        printf("You chose option number %d\n", choice);
                        correct = 1;
                        break;
                    }
                    if(j == sizeof(dialogs[i].decisionOptions) / sizeof(dialogs[i].decisionOptions[0])){ // If option was invalid, retry
                        printf("Your election wasn't in the option list, try again\n");
                        // decision, again
                        printDecision(dialogs[i]);
                    }
                }
            } while(correct == 0);
        }
        // update script progress
        if(i == sizeof(dialogs[i]) / sizeof(dialog)){
            scriptProgress += i;
            char envProgress[1024];
            sprintf(envProgress, "SCRIPT_PROGRESS=%d", scriptProgress);
            if(putenv(envProgress) != 0){
                perror("Couldn't update scriptProgress at env, the program might have behavioral issues");
            }
        }
    }
}