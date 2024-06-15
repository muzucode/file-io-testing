#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_LINES_ARRAY_SIZE 10

char** readLinesFromFile(char* filename, int* count) {
    FILE *file = fopen(filename, "r");
    char buf[512];
    int linesArrSize = INITIAL_LINES_ARRAY_SIZE;

    char** lines = (char**)malloc(sizeof(char*) * linesArrSize);


    *count = 0;

    while( fgets(buf, sizeof(buf), file) ) {
        buf[strcspn(buf, "\n")] = '\0';

        lines[*count] = strdup(buf);
        if(lines[*count] == NULL ) {
            perror("Error allocating memory for line");
        }

        (*count)++;

        // Handle if lines array needs to be resized
        if(*count >= linesArrSize) {

            linesArrSize *= 2;
            // Realloc lines variables
            char** temp = (char**)realloc(lines, linesArrSize * sizeof(char*));
            if ( temp == NULL ){
                perror("Error re-allocating memory");
            }
            lines = temp;
        }
    }
    
    return lines;


}


int main() {
    int count;
    char* filename = "pages-to-download.txt";

    char** lines = readLinesFromFile(filename, &count);

    return 0;
}
