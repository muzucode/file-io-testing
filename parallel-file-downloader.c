#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>


void writeFile(char* filepath) {
    FILE* file;
    char buf[30] = "My content goes here\n";

    file = fopen(filepath, "w");
    fprintf(file, "%s", buf);

    fclose(file);

    return;
}

char* readFile(char* filepath) {
    char* contents;
    FILE* file;
    unsigned int fileSize;

    file = fopen(filepath, "r");

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    contents = (char*)malloc(sizeof(fileSize) + 1);
    if ( contents == NULL ) {
        perror("Problem mallocing contents in readFile()");
        exit(1);
    }

    size_t bytesRead = fread(contents, sizeof(char), fileSize, file);
    contents[bytesRead+1] = '\0'; // Null-term the contents


    return contents;
}


int downloadFile(char* path) {
    FILE* file;
    pid_t p;

    printf("Example path: %s\n", path);


    // Run forked process
    p = fork();

    if (p<0) {
        perror("Error forking");
        exit(1);
    }
    else if ( p == 0) {
        printf("Running in child process!  %d\n", getpid());
    }
    else {
        printf("Running in parent process!  %d\n", getpid());
    }

    close(p);

    return 0;
}




int main() {
    char* examplePath = "files-to-download.txt";
    char* contents;


    // downloadFile(examplePath);

    // Read file
    contents = readFile(examplePath);

    printf("%s", "The file contents: \n");
    printf("%s\n", contents);

    free(contents);

    return 0;
}
