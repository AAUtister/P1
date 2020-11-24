#include "reader.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mighty shit

int main() {
    int x = 0;
    char ** verb_array = ReadVerbFromFile();
    char ** tekst_array = ReadTextFromFile();

    int c = 0;
    while (tekst_array[c] != NULL) {
        c++;
    }

    int binary_shit[c];

    while (x <= c-1){
        for (int i = 0; i <= 44233; i++){

            if (strcmp(tekst_array[x], verb_array[i])){
                binary_shit[x] = 0;
            }
            else{
                printf("\nFundet paa , %d plads, ordet er %s", i, tekst_array[x]);
                binary_shit[x] = 1;
                x++;
            }
        }
        x++;
    }
    FILE *output;
    output = fopen("output.txt", "w");

    int iterator = 0;
    while (iterator < c) { // For hvert ord
        int p = 0;
        if (binary_shit[iterator] == 1) { // Check om det er verbum
            while (tekst_array[iterator][p] != '\0') {
                fprintf(output, "%c", toupper(tekst_array[iterator][p]));
                p++;	

            }fprintf(output, " ");
        } else {
            while (tekst_array[iterator][p] != '\0') {
                fprintf(output, "%c", tekst_array[iterator][p]);
                p++;	
            }}
        fprintf(output, " ");
        iterator++;
    }
    fclose(output);
    free(tekst_array);
    free(verb_array);
    return 0;
}
