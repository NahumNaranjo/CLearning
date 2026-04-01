#ifndef CCMANAGER_CONFIG_H
#define CCMANAGER_CONFIG_H
    #include <cui2.h>
    #include <string.h>
    #include "ccmanager.h"
    #include <hermes.h>
    void displayCCManagerUI();
    void displayConfigs(configFormat* info, char* mode, char* path);
    char* getPath();
#endif