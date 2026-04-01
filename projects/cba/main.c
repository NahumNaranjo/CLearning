#include "cba.h"
#include "ui.h"
#include <hermes.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: cba [build|clean|init]\n");
        return 1;
    }
    
    if(strcmp(argv[1], "build") == 0) {
        build();
    }
    else if(strcmp(argv[1], "clean") == 0) {
        clean();
    }
    else if(strcmp(argv[1], "init") == 0) {
        init();
    }
    else {
        printf("Unknown command: %s\n", argv[1]);
    }
    
    return 0;
}