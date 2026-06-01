#include "ui.h"


char BuildUI(){
    MenuOption options[] = {
        {"Analyze File", "a"},
        {"Load Report", "l"},
        {"Exit", "e"}
    };
    Menu* menu = createMenu("CXT - Text Analyzer", options, 3);
    char result = *displayMenu(menu);
    freeMenu(menu);
    return result;
}

char* AnalysisUI(){
    static char option[256]; // Buffer for input
    printf("CXT Analysis Menu:\n");
    printf("Type 'exit' to return to the main menu.\n");
    if (!fgets(option, sizeof(option), stdin)) {
        printf("Error reading input\n");
        return NULL;
    }
    // Remove newline
    size_t len = strlen(option);
    if (len > 0 && option[len-1] == '\n') {
        option[len-1] = '\0';
    }
    return option;
}
void Help(){
    printf("CXT Help Menu:\n");
    printf("1. To use the program, enter the full path of the text file you want to analyze.\n");
    printf("2. The program will count the total number of words and identify the most common word.\n");
    printf("3. To exit the program, type 'exit' when prompted for a file path.\n");
    printf("4. When in analysis mode, only the following commands will be recognized:\n");
    printf("   - 'exit': Exits analysis mode and returns to main menu.\n");
    printf("   - 'help': Displays this help menu.\n");
    printf("   - Any other input will be ignored during analysis.\n");
    printf("5. For further assistance, refer to the documentation or contact support.\n");
    Stop();
    clearConsole();
}

void analysisMode(char* txt, size_t* size, AnalyzeTextData* dataOut){
    char* ptrToOption;
    AnalyzeTextData* data;
    if(txt){
        printf("Analyzing file...\n");
        data = AnalyzeText(txt, size);
    } else{
        data = dataOut;
    }
    while(1){
            clearConsole();
            ptrToOption = AnalysisUI();
            if(strcmp(toLowerCase(ptrToOption), "exit") == 0) {printf("Exiting analysis mode.\n"); clearConsole(); break;}
            if(strcmp(toLowerCase(ptrToOption), "help") == 0) {Help(); continue;}
            if(strstr(toLowerCase(ptrToOption), "info") != NULL){
                if(strstr(ptrToOption, "-l") != NULL){
                    printf("Number of lines: %i\n", *data->newLines);
                }
                if(strstr(ptrToOption, "-w") != NULL){
                    printf("Number of words: %i\n", *data->words);
                }
                if(strstr(ptrToOption, "-m") != NULL){
                    printf("Most common word: %s\n", data->mostUsed);
                }
                if(strstr(ptrToOption, "-f") != NULL){
                    printf("All word frequencies:\n");
                    for(size_t i = 0; i < data->uniqueWords; i++){
                        printf("Word: %s - Frequency: %i\n", data->tracker[i].key, data->tracker[i].timesAppeared);
                    }
                }
                if(strstr(ptrToOption, "-a") != NULL){
                    printf("Number of lines: %i\n", *data->newLines);
                    printf("Number of words: %i\n", *data->words);
                    printf("Most common word: %s\n", data->mostUsed);
                    printf("All word frequencies:\n");
                    for(size_t i = 0; i < data->uniqueWords; i++){
                        printf("Word: %s - Frequency: %i\n", data->tracker[i].key, data->tracker[i].timesAppeared);
                    }
                }
            } 
            if(strcmp(ptrToOption, "write") == 0){
                char* path = getFilePath();
                writeFile(path, data);
                printf("Analysis report written to %s\n", path);
            }
            Stop();
        }
}