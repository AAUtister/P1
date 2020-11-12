#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// void binary_search() {
//
// }

char ** diller() {
    FILE *file_p = fopen("verbs_ascii_friendly.txt", "r");
    int i = 0;
    int x = 0;
    char file_content[600000];
    const char s[3] = "\n";
    char *token;
    char ** verb_array = malloc(442292 * sizeof(char*));

    if (file_p == NULL) {
            printf("Fejl. Filen kunne ikke findes.\n");
            exit(EXIT_FAILURE);
    }
   
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file_p)) != -1) {
        strcat(file_content, line);
    }

    fclose(file_p);
    
    token = strtok(file_content, s);

    while(token != NULL) {
        verb_array[i++] = token;
        token = strtok(NULL, s);
    };
    
    return verb_array;
}