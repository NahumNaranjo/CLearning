#ifndef GENERALDATA_H
#define GENERALDATA_H
    #include <stdio.h>
    #include <cxtMap.h>
    typedef struct {
        char version[50];
        char name[100];
        char cmakeMinVersion[20];
        char ninjaMinVersion[20];
        char output[100];
    } BuildInfo;
    typedef struct  {
        char mode;
    } calcData;


#endif