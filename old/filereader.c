#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>


char* readFile(char* pathname) {
    FILE* file;
    char* contents;
    long fileSize;


    file = fopen(pathname, "r");

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    contents = (char*)malloc(fileSize + 1);
    size_t bytesRead = fread(contents, sizeof(char), fileSize, file);

    contents[bytesRead+1] = '\0';

    fclose(file);

    return contents;
    
}


int main() {
    char* filecontents;

    // Read the file!
    filecontents = readFile("files-to-download.txt");

    downloadFilesFromList();
    
    printf("My file contents: \n");
    printf("%s\n", filecontents);

    free(filecontents);
    return 0;
}