#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define INITIAL_ARRAY_SIZE 10

// Function to read file paths (URLs) from a file and store them in an array of strings
char** readFilePaths(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Allocate initial memory for the array of strings
    int arraySize = INITIAL_ARRAY_SIZE;
    char** paths = (char**)malloc(arraySize * sizeof(char*));
    if (paths == NULL) {
        perror("Error allocating memory for paths array");
        fclose(file);
        return NULL;
    }

    char buffer[MAX_LINE_LENGTH];
    *count = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';

        // Allocate memory for the string and copy the line into it
        paths[*count] = strdup(buffer);
        if (paths[*count] == NULL) {
            perror("Error allocating memory for path string");
            // Free previously allocated strings and the array
            for (int i = 0; i < *count; i++) {
                free(paths[i]);
            }
            free(paths);
            fclose(file);
            return NULL;
        }

        (*count)++;

        // Resize the array if necessary
        if (*count >= arraySize) {
            arraySize *= 2;
            char** temp = (char**)realloc(paths, arraySize * sizeof(char*));
            if (temp == NULL) {
                perror("Error reallocating memory for paths array");
                // Free previously allocated strings and the array
                for (int i = 0; i < *count; i++) {
                    free(paths[i]);
                }
                free(paths);
                fclose(file);
                return NULL;
            }
            paths = temp;
        }
    }

    fclose(file);
    return paths;
}

int main() {
    const char* filename = "files-to-download.txt";
    int count;
    char** filepaths = readFilePaths(filename, &count);

    if (filepaths == NULL) {
        fprintf(stderr, "Failed to read file paths\n");
        return 1;
    }

    printf("File paths:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", filepaths[i]);
        free(filepaths[i]); // Free each string after use
    }
    free(filepaths); // Free the array of strings

    return 0;
}
