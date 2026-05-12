#ifndef CCSV_H
#define CCSV_H
    #include <stdio.h>
    #include <string.h>
    #include <clist.h>
    #include <ariadne.h>

    static inline int isKeyword(char** keywords, int count){
        for(int i = 0; i < count; i++){
            
        }
    }
    static inline List convert(char* path, char* keywords){
        if(strstr(path, ".csv") == NULL){
            printf("That's not a valid CSV file. Returning to main menu.\n");
            return;
        }

        FILE* fp = fopen(path, "r");
        if(!fp){
            printf("Couldn't open the file.\n");
            return;
        }
        
        trimWhitespace(keywords);
        char* keywordsArray[256] = {0};
        int position = 0;
        int charNum = 0;
        for(int i = 0; keywords[i]; i++){
            if(keywords[i] == ',') {
                position++;
                charNum = 0;
                continue;
            }
            keywordsArray[position][charNum] = keywords[i];
        }

        int count = 0;
        char buffer[1024];
    
        while(fgets(buffer, sizeof(buffer), fp)){
            buffer[strcspn(buffer, "\n")] = 0;

            List results = createList(256);
            char* token = strtok(buffer, ",");
            
            while(token){
                if(isKeyword(keywordsArray, position)){
                    token = strtok(NULL, ",");
                    continue;
                }
                add(&results, token);
                count++;
                token = strtok(NULL, ",");
            }
        }
        fclose(fp);

    }
#endif