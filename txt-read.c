#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    FILE *file_p = fopen("/Users/frederikfrohn/P1/txt/tekst1.txt", "r");
    int i = 0;
    int x = 0;
    char tekst[100];
    const char s[2] = " \n";
    char *token;
    char *tekst_array[50];

    if (file_p == NULL) {
            printf("Fejl. Filen kunne ikke findes.\n");
            exit(EXIT_FAILURE);
    }
    
    // fgets(tekst, 100, file_p);

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file_p)) != -1) {
        strcat(tekst, line);
    }


    fclose(file_p);
    
    token = strtok(tekst, s);


    while(token != NULL) {
        // printf("%s\n", token);
        tekst_array[i++] = token;
        token = strtok(NULL, s);
        
    };
        
    printf("Array: %d", i);

    // i--;

    // Printer array
    for (x = 0; x < i; x++){
        printf("\n%s", tekst_array[x]);
        //(Pelle og benjamins funktion)
    }

    printf("\n%s", tekst_array[9]);
    
    return 0;    
}