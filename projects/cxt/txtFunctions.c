#include "txtFunctions.h"

AnalyzeTextData* AnalyzeText(char* txt, size_t* size) {
    return (AnalyzeTextData*)commonAnalyzeText(txt, size);
}
