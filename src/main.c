#include "reader.h"
#include "rules.h"
#include "word.h"
#include "sen_splitter.h"
#include "minixml.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "utf8.h"


// TODO: Find ud af om det skal vaere hardkodet eller mulighed for begge ting
#define VERBSFILE "data/verbs_ascii_friendly.txt"
#define INPUTFILE "data/input.txt"

// Mighty shit
// ToDo: Tilfoej flere ordklasser at sortere efter

int main() {
    setlocale(LC_ALL, "da_DK.UTF-8");
    int length_verb = 0;
    int length_tekst = 0;
    int x = 0;
    int i = 0;


    char **verb_array = read_from_file(VERBSFILE, &length_verb, "\n");
    char **tekst_array = read_from_file(INPUTFILE, &length_tekst, " \n");
    char **senten_array = sentence_splitter(INPUTFILE);

  

    int tekst_count = 0;
    while (tekst_array[tekst_count] != NULL) {
        tekst_count++;
    }
        
    word * wArr;
    wArr = (word *) calloc(sizeof(wArr), sizeof(word) + 1000);
    wArr_maker(tekst_array, wArr);

    for (int i = 0; i < tekst_count; i++) {
        printf("ORD #%d: %s\n", i, wArr[i].word);
        printf("KLASSE #%d: %s\n", i, GetTypeString(wArr[i].type));
    }

    while (senten_array[i] != NULL){
        printf("Array = %s \n", senten_array[i]);
        i++;
    }

    int *found_rule = malloc(tekst_count * sizeof(int) * 8);

    rules(tekst_array, found_rule);
    

    for (i = 0; i < tekst_count; i++) {
        printf("Found rule: %d\n", found_rule[i]);
    }


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
        if ((found_rule[itr+1] == 0) && (itr != tekst_count - 1)) {
            while (wArr[itr].word_org[p] != '\0') {
                fprintf(output, "%c", wArr[itr].word_org[p]);
                p++;    
            }
            fprintf(output, "%c", ','); 
        } else {
            while (wArr[itr].word_org[p] != '\0') {
                fprintf(output, "%c", wArr[itr].word_org[p]);
                p++;	
            }
        }
        fprintf(output, " ");
        itr++;
    }

    fclose(output);





    /* Free memory */
    free(wArr);
    free(found_rule);
    free(tekst_array);
    free(verb_array);
    return 0;
}
