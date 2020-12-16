#include "reader.h"
#include "word.h"
#include "rules.h"
#include "sen_splitter.h"
#include "minixml.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "utf8.h"
#include "nexus.h"

// TODO: Find ud af om det skal vaere hardkodet eller mulighed for begge ting
#define VERBSFILE "data/verbs_ascii_friendly.txt"
#define INPUTFILE "data/input.txt"

// Mighty shit
// ToDo: Tilfoej flere ordklasser at sortere efter

void komma_function(int *found_nexus, int *found_rule, int tekst_count, word *wArr);

int main() {
    setlocale(LC_ALL, "da_DK.UTF-8");
    int length_tekst = 0;
    int * found_nexus;
    
    char **tekst_array = read_from_file(INPUTFILE, &length_tekst, " \n");


    int tekst_count = 0;
    while (tekst_array[tekst_count] != NULL) {
        tekst_count++;
    }
        
    word * wArr;
    wArr = (word *) calloc(sizeof(wArr), sizeof(word) + 1000);
    wArr_maker(tekst_array, wArr);
    for (int i = 0; i < tekst_count; i++) {
    	printf("Ord: %s - Ordklase: %d\n", wArr[i].word_org, wArr[i].type);
    }
  

    int *found_rule = malloc(tekst_count * sizeof(int) * 8);

    rules(tekst_array, found_rule, wArr);

    found_nexus = nexus(wArr, tekst_count, length_tekst);
    
    for(int i = 0; i < tekst_count;i++){
        printf("\n%s - FOUND NEXUS: %d \n", wArr[i].word_org, found_nexus[i]);
    }

    komma_function(found_nexus, found_rule, tekst_count, wArr);

    free(tekst_array);
    
    return 0;
   
}
void komma_function(int *found_nexus, int *found_rule, int tekst_count, word *wArr){
    /* Skriv output til fil */
    FILE *output;
    output = fopen("output.txt", "w");
    int itr = 0;

    while (itr < tekst_count) { // For hvert ord
        int p = 0;
        
        if ((found_rule[itr+1] == 1) && (itr != tekst_count - 1)) {
            while (wArr[itr].word_org[p] != '\0') {
                fprintf(output, "%c", wArr[itr].word_org[p]);
                p++;    
            }
            fprintf(output, "%c", ','); 
        
        } else if((found_nexus[itr+1] == 1) && (itr != tekst_count - 1) && (found_rule[itr+1] != 2)){
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
    free(found_nexus);
}
