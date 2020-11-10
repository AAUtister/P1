#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    FILE *file_p = fopen("test.txt", "r");
    int i = 0;
    int x = 0;
    char tekst[1000];
    const char s[2] = " ";
    char *token;
    char *tekst_array[1000];

    if (file_p == NULL) {
            printf("Fejl. Filen kunne ikke findes.\n");
            exit(EXIT_FAILURE);
    }
    
    /* fseek(file_p, 0L,SEEK_END);
    long int ret = ftell(file_p);
    printf("File size is %ld", ret);  Læser størrelsen af filen */ 

    if( fgets (tekst, 1000, file_p) !=NULL) {
        puts(tekst);
    }
    fclose(file_p);
    
    token = strtok(tekst, s);


    while(token != NULL) {
        printf("%s\n", token);
        tekst_array[i++] = token;
        token = strtok(NULL, s);
        
    };
    
    // i = st�rrelsen af filen.
    
    printf("\n\nArray:");

    // Printer array
    for (x = 0; x < i; x++){
        printf("\n%s", tekst_array[x]);
    }

    printf("\n%s",tekst_array[i]); //Eksempel
    
    return 0;    
}