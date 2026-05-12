#include "ui.h"
#include "readFile.h"
#include "txtFunctions.h"
#include "writeFile.h"
#include <stdlib.h>
#include <string.h>
#include <hermes.h>
#include <cfm2.h>
#include <cui2.h>

int main(){
    int c;
    clearConsole();
    while(1){
        displayTitle("CXT - C Text Analyzer");
        char ptrToOption = BuildUI();
        size_t size;
        AnalyzeTextData* data;
        if (!ptrToOption) continue;
        switch(ptrToOption){
            case 'e':
                clearConsole(); 
                return 0;
                break;
            case 'l':
                WIN32_FIND_DATA* files = listFiles("analysis_report_", "cxt\\reports");
                if(files == NULL || files[0].cFileName[0] == '\0'){ 
                    printf("No report files found.\n");
                    Stop();
                    clearConsole();
                    continue;
                }
                
                for(int i = 0; files[i].cFileName[0] != '\0'; i++){ 
                    printf("    %d- %s\n", i, files[i].cFileName);
                }
                
                char* input = readInput("Please, select your desired file:\n", 128);
                if(input == NULL || input[0] == '\0'){  
                    printf("Invalid number... Try again\n");
                    continue;
                }
                
                int idx = atoi(input);
                if(idx < 0 || files[idx].cFileName[0] == '\0'){ 
                    printf("Invalid selection... Try again\n");
                    continue;
                }
                
                char fp[2048];
                snprintf(fp, sizeof(fp), "%scxt\\reports\\%s", getRootFilePath(), files[idx].cFileName);
                data = parseReportFiles(readFile(fp, 0));
                if(data == NULL){  
                    printf("Error reading report file.\n");
                    continue;
                }
                analysisMode(NULL, 0, data);
                continue;
                break;
            case 'a':
                char* address = readInput("Please, write your address here:\n", 512);
                if(address == NULL){
                    printf("Not valid address found.\n");
                    continue;
                }
                analysisMode(readFile(address, 0), 0, NULL);
                continue;
                break;
            case 'h':
                Help(); 
                continue;
                break;
        }
    }   
}