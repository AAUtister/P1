#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    FILE *file_p = fopen("/Users/frederikfrohn/P1/txt/verbs_ascii_friendly.txt", "r");
    int i = 0;
    int x = 0;
    char file_content[600000];
    const char s[3] = "\n";
    char *token;
    char *verb_array[60000];

    if (file_p == NULL) {
            printf("Fejl. Filen kunne ikke findes.\n");
            exit(EXIT_FAILURE);
    }
   
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    strcpy(file_content, "_VERBS_\n");

    while ((read = getline(&line, &len, file_p)) != -1) {
        strcat(file_content, line);
    }

    fclose(file_p);
    
    token = strtok(file_content, s);


    while(token != NULL) {
        verb_array[i++] = token;
        token = strtok(NULL, s);
    };
    
    // printf("NY NY NY NY NY NY %d", i);

    // Printer array
    for (x = 0; x < i; x++){
        printf("\n%s", verb_array[x]);
    }

    printf("\n%s", verb_array[31]); // Eksempel på at tage et ord
    printf("\n%c", verb_array[31][0]); // Eksempel på at tage et bogstav
    
    return 0;
}