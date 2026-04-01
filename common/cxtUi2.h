#ifndef CXTUI2_H
#define CXTUI2_H
    #include <stdio.h>
    #include "writeFile2.h"
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include "txtFunctions2.h"
    #include "hermes.h"
    #include "cui2.h"

    char BuildUI();
    void Help();
    char* HelpUI();
    void analysisMode(char* txt, size_t* size, CommonAnalyzeTextData* dataOut);
#endif