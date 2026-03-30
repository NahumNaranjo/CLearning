#include "ccmui.h"

char* getPath(){

    MenuOption options[] = {
        {"Read .config", "r"},
        {"Modify .config", "m"},
        {"Append to an existing .config", "a"}
    };
    Menu* menu = createMenu("C Config Manager", options, 0);
    displayTitle(menu->title);
    char result = displayMenu(menu);
    
    printf("Now write your (absolute) file's address:\n");
    char* path = readLIne();

    if(result == 'a' || result == 'r'){
        FILE* fp = fopen(path, "r");
        if(!fp){
            printf("Couldn't find that file, please, try again... \n");
            fclose(fp);
            return NULL;
        }
        fclose(fp);
        char* returning[] = {path, result};
        return path;
    }
    return NULL;
}

// Displays all config args for the user to select
void displayConfigs(configFormat* info, char* mode, char* path){
    //dispkays all arg and val
    for (int i = 0; info[i].val; i++){
        if((strlen(info[i].arg) + 7) >= 40 || 
        (strlen(info[i+1].arg) + 7) >= 40)
        {
            printf("%d. %s - %s\n", i, info[i].arg, info[i].val);
            continue;
        }
        printf(
            "%d. %s - %s | %d. %s - %s\n", i, info[i].arg, info[i].val, //first argument and structure
            i+1, info[i+1].arg, info[i].val // second argument
        );
        i++;
    }

    char numbers[] = {
        '1', '2', '3',
        '4', '5', '6',
        '7', '8', '9',
        '0', '\0'
    };

    switch (mode[0]){
        case 'a':
            printf("The format is the following (please, dont use spaces): \"arg,value;arg,value;\"\n");
            char* res = readLine();
            char* copy = res;
            char* token;
            char* tokens[4096];
            size_t count = 0;
            configFormat format[4096];
            token = strtok(res, ";");
            for(int i = 0; token; i++){
                tokens[i] = token;
                token = strtok(NULL, ";");
                count = i+1;
            }
            tokens[count] = '\0';
            size_t pos = 0;
            char* newToken;
            for(int i = 0; tokens[i]; i++){
                newToken = strtok(tokens[i], ",");
                format[i].arg = newToken;
                newToken = strtok(NULL, ",");
                format[i].val = newToken;
                pos = i+1;
            }
            format[pos].val = "\0";
            appendConfigFile(format, path);
            printf("Saved!");
        break;
        case 'm':
            printf("Write the number of the line you wanna modify: \n");
            char* choice = readLine();
            char result[128] = {0};  // Initialize to zeros
            int resIdx = 0;
            // cleans result
            for(int i = 0; choice[i]; i++){
                for(int j = 0; numbers[j]; j++){
                    if(choice[i] == numbers[j]){
                        result[resIdx++] = numbers[j];
                        break;
                    }
                }
            }
            result[resIdx] = '\0'; 
        
            //parses
            int resInt = atoi(result);
            if(!resInt) {
                printf("Couldn't parse your choice...\n");
                return NULL;
            }
            printf("Previous value: \n");
            printf("%d. %s - %s\n", resInt, info[resInt].arg, info[resInt].val);
            printf("New value (write it exactly as you want it to be): \n");
            info[resInt].val = readLine();
            writeConfigFile(info, path);
            printf("Your file has been correctly modified\n");
        break;
    }
}

// sort of main.c
void displayCCManagerUI(){
    char* result;
    do {
        result = getPath();
    } while(!result);
    displayConfigs(readConfigFile(result[0]), result[1], result[0]);
}