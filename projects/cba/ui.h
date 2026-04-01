#ifndef UI_H
#define UI_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "cba.h"
    #include <cfm2.h>
    #include <ariadne.h>
    #include <hermes.h>
    #include <windows.h>
    #include <stdbool.h>
    char* BuildUI();
    void config(char* type);
    void Help();
    void writeConfigFile(char* path);
#endif