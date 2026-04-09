#ifndef DIALOG_H
#define DIALOG_H
    #include <stdio.h>
    #include <hermes.h>
    #include <stdlib.h>

    typedef struct {
        char* name;
        char* text;
        char type;
        char* decisionText;
        char** decisionOptions;
    } dialog;

    void dialogSequence(dialog* dialogs);
    void printDecision(dialog dec);
#endif