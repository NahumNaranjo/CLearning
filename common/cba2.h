#ifndef CBA2_H
#define CBA2_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <direct.h>
    #include <windows.h>
    #include <string.h>
    #include <lookForRootFiles.h>
    #include <ariadne.h>
    #include <generalData.h>
    #include <cfm2.h>

    void build();
    void prepare(BuildInfo* buildInfo);
    void detectProject(BuildInfo* buildInfo);
    void generateBuildFile(BuildInfo* buildInfo);
    void clean();
    void generateFiles();
    void generateCMake(BuildInfo* buildInfo);
    int shouldIncludeDirectory(const char* dir);
    void runCMake();
    void init();
    void BuildParser(FILE* file, BuildInfo* buildInfo);
    
#endif