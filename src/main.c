#include "reader.h"
#include "rules.h"
#include "word.h"
#include "sen_splitter.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TODO: Find ud af om det skal vaere hardkodet eller mulighed for begge ting
#define VERBSFILE "data/verbs_ascii_friendly.txt"
#define INPUTFILE "data/input.txt"

// Mighty shit
// ToDo: Tilfoej flere ordklasser at sortere efter

int main() {
    int length_verb = 0;
    int length_tekst = 0;
    int x = 0, i = 0;
    char **verb_array = read_from_file(VERBSFILE, &length_verb, "\n");
    char **tekst_array = read_from_file(INPUTFILE, &length_tekst, " \n");
    char **senten_array = sentence_splitter(INPUTFILE);
    int tekst_count = 0;
    while (tekst_array[tekst_count] != NULL) {
        tekst_count ++;
    }

    while (senten_array[i] != NULL){
        printf("Array = %s \n", senten_array[i]);
        i++;
    }

    int *found_rule = malloc(tekst_count * sizeof(int) + 1000);

    rules(tekst_array, found_rule);
    

    int verb_count = 0;
    while (verb_array[verb_count] != NULL) {
        verb_count++;
    }

    /* Skriv Output til terminal */
    int word_class[tekst_count];
    while (x < tekst_count){
        for (int i = 0; i < verb_count; i++){
            if (strcmp(tekst_array[x], verb_array[i])){
                word_class[x] = 0;
            }
            else{
                printf("\nFundet paa , %d plads, ordet er %s", i, tekst_array[x]);
                word_class[x] = 1;
                x++;
            }
        }
        x++;
    }

    /* Skriv output til fil */
    FILE *output;
    output = fopen("output.txt", "w");
    int itr = 0;
    while (itr < tekst_count) { // For hvert ord
        int p = 0;
        if (word_class[itr] == VERB) {
            while (tekst_array[itr][p] != '\0') {
                fprintf(output, "%c", toupper(tekst_array[itr][p]));
                p++;	

            }fprintf(output, " ");
        } else {
            while (tekst_array[itr][p] != '\0') {
                fprintf(output, "%c", tekst_array[itr][p]);
                p++;	
            }
        }
        fprintf(output, " ");
        itr++;
    }
    fclose(output);
    
    /* Free memory */
    free(tekst_array);
    free(verb_array);
    return 0;
}
