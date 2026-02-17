#include "cl.h"
#include "map.h"

void interpreter(int argc, char** argv){
    // Version info
    if(argc == 1){
        printf("CL (Ecosystem) version 1.2.0. Author: Nahum Naranjo \n");
        return;
    }
    if(argv[1] == NULL){
        return;
    }
    if (argv[1] != NULL && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)) {
        if(argv[2] == NULL) {
            printf("CL (Ecosystem) version 1.2.0. Author: Nahum Naranjo \n"); 
            return;
        }
        if(strcmp(argv[2], "cxt") == 0){
            printf("CXT version 1.0.3. Author: Nahum Naranjo \n");
        }
        if(strcmp(argv[2], "cba") == 0){
            printf("CBA version 1.0.0 BETA. Author: Nahum Naranjo \n");
        }
        if(strcmp(argv[2], "cl") == 0){
            printf("CL version 2.0.0. Author: Nahum Naranjo");
        }
        if(strcmp(argv[2], "hub") == 0){
            printf("CL version 1.0.1. Author: Nahum Naranjo");
        }
        return;
    }

    //Help info
    if (argv[1] != NULL && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("CL - A bunch of tools made with pure C\n");
        printf("Usage: cl [options] [tool/hub]\n");
        printf("Options:\n");
        printf("  -v, --version       Show version information\n");
        printf("  -h, --help          Show this help message\n");
        printf("  exec, -e            Execute a tool, usage: \"cl exec [toolName]\" (also works with hub)\n");
        return;
    }
    // Exec
    if((strcmp(argv[1], "exec") == 0 || strcmp(argv[1], "-e") == 0)){
        if(argc < 2) return;
        // Executing specific commands from cl
        if(strcmp(argv[2], "cxt") == 0){
            char* path = argv[3];
                for(int i = 0; path[i]; i++) {
                if(path[i] == '\\') path[i] = '/';
            }
            char* inst = argv[4];
            size_t size;
            char* fileData = readFile(path, &size);
            AnalyzeTextData* data = AnalyzeText(fileData, &size);
            if(data == NULL) printf("Something went wrong while readint the file");
            if(path != NULL){
                // Write
                if(strcmp(inst, "write") == 0){
                    path = getFilePath();
                    writeFile(path, data);
                    printf("Your analysis has been written to %s\n", path);
                    return;
                }
                // Info options
                if(strcmp(inst, "info") == 0){
                    char* spec = argv[5];
                    if(strcmp(spec, "-a") == 0){
                        printf("Number of lines: %i\n", *data->newLines);
                        printf("Number of words: %i\n", *data->words);
                        printf("Most common word: %s\n", data->mostUsed);
                        printf("All word frequencies:\n");
                        for(size_t i = 0; i < data->uniqueWords; i++){
                            printf("Word: %s - Frequency: %i\n", data->tracker[i].key, data->tracker[i].timesAppeared);
                        }
                        return;
                    }
                    if(strcmp(spec, "-l") == 0){
                        printf("Number of lines: %i\n", *data->newLines);
                        return;
                    }
                    if(strcmp(spec, "-w") == 0){
                        printf("Number of words: %i\n", *data->words);
                        return;
                    }
                    if(strcmp(spec, "-f") == 0){
                        printf("All word frequencies:\n");
                        for(size_t i = 0; i < data->uniqueWords; i++){
                            printf("Word: %s - Frequency: %i\n", data->tracker[i].key, data->tracker[i].timesAppeared);
                            return;
                        }
                    }
                    if(strcmp(spec, "-m") == 0){
                        printf("Most common word: %s\n", data->mostUsed);
                        return;
                    }
                }
                if(inst == NULL){
                    analysisMode(NULL, &size, data);
                    return;
                }
            }
        }
        if(strcmp(argv[2], "cba") == 0){
            char* inst = argv[3];
            if(strcmp(inst, "build") == 0){
                Build();
                return;
            }
            if(strcmp(inst, "prepare") == 0){
                printf("Preparing...\n");
                BuildInfo* build;
                FILE* fp = lookForRootFiles("\\configs\\cba.config", "r");
                BuildParser(fp, build);
                prepare(build);
                printf("Your files are ready to use\n");
                return;
            }
            if(strcmp(inst, "generate") == 0 ||strcmp(inst, "-g") == 0){
                printf("Generating...\n");
                generateFiles();
                printf("Done!");
                return;
            }
        }
        // Direct exec
        if(strcmp(argv[2], "1") == 0){
            system("cxt.exe");
        }
        if(strcmp(argv[2], "2") == 0){
            system("cba.exe");
        }
    }
    if(argv[1] != NULL && (strcmp(argv[1], "exec") == 0 || strcmp(argv[1], "-e") == 0)){
        if(argv[2] != NULL){
            printf("Interpreting tool: %s\n", argv[2]);        
        } 
        else{
            printf("No tool provided to interpret.\n");
            return;
        }
        if(strcmp(argv[2], "hub") == 0){
            printf("Going to the hub...");
            system("hub.exe");
        }
        if(strcmp(argv[2], "cxt") == 0){
            printf("Executing CXT...");
            system("cxt.exe");
        }
        if(strcmp(argv[2], "cba") == 0){
            printf("Executing CBA...");
            system("cba.exe");
        }
        return;
    }
    

    // Unknown option
    // TODO: Add cl install to install libraries to projects
    printf("Unknown option: %s\n", argv[1]);
    printf("Use -h or --help for usage information.\n");
    return;
}
