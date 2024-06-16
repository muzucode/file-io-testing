#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define INITIAL_ARR_SIZE 10


char** getPathsFromFile(char* filename, int* count) {
    FILE *file = fopen(filename, "r");
    char lineBuf[512];
    char** paths;
    int arrSize = INITIAL_ARR_SIZE;

    paths = (char**)malloc(INITIAL_ARR_SIZE * sizeof(char*));

    while(fgets(lineBuf, sizeof(lineBuf), file)) {
        lineBuf[strcspn(lineBuf, "\n")] = '\0';

        paths[*count] = strdup(lineBuf);
        (*count)++;

        if(*count >= arrSize) {
            arrSize *=2 ;
            char** temp = (char**)realloc(paths, sizeof(char*) * arrSize);
            if(temp == NULL) {
                perror("Reallocing errored out");
                free(paths);
                for(int i = 0; i < *count; i++) {
                    free(paths[i]);
                }
                fclose(file);
            }

            paths = temp;
        }
    }

    fclose(file);

    return paths;

}


int main() {
    char** paths;
    char* filename = "path-lines.txt";
    int count;

    paths = getPathsFromFile(filename, &count);
    printf("Number of lines in file: %d\n", count - 1);


    for(int i = 0; i < count; i++) {
        printf("Line read: %s\n", paths[i]);
        free(paths[i]);
    }

    free(paths);

    return 0;
}