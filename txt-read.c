#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char ** ReadTextFromFile() {
    FILE *fp;
   int lenght;

   fp = fopen("tekst1.txt", "r");

   fseek(fp, 0, SEEK_END);

   lenght = ftell(fp);

   fclose(fp);

   printf("Total size of file.txt = %d bytes\n", lenght);
    
    
    FILE *file_p = fopen("tekst1.txt", "r");
    int i = 0;
    char tekst[10000]; // lenght virker ikke ordenligt
    const char s[4] = " \n";
    char *token;
    char ** tekst_array = calloc(199, sizeof(char*)); // Giver segfault med malloc fordi den ikke garantere at heapen er null ifoelge Anders


    if (file_p == NULL) {
            printf("Fejl. Filen kunne ikke findes.\n");
            exit(EXIT_FAILURE);
    }
    
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file_p)) != -1) {
        strcat(tekst, line);
    }


    fclose(file_p);
    
    token = strtok(tekst, s);


    while(token != NULL) {
        tekst_array[i++] = token;
        token = strtok(NULL, s);
        
    };
        
    return tekst_array;
}
