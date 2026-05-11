#ifndef INSTALL_H
#define INSTALL_H
    #include <string.h>
    #include <cfm2.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #ifdef __WIN32
        #include <direct.h>
    #elif __APPLE__ || __linux__
        #include <uninstd.h>
        #include <sys/stat.h>
    #endif
    void* clInstall(char* name);
#endif