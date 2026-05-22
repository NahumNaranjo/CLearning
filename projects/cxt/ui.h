#ifndef UI_H
#define UI_H
    #include <stdio.h>
    #include "writeFile.h"
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include "txtFunctions.h"
    #include <hermes.h>
    #include <cui2.h>

    char BuildUI();
    void Help();
    char* AnalysisUI();
    void analysisMode(char* txt, size_t* size, AnalyzeTextData* dataOut);
#endif