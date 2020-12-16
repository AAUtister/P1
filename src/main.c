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
#include "nexus.h"

// TODO: Find ud af om det skal vaere hardkodet eller mulighed for begge ting
#define VERBSFILE "data/verbs_ascii_friendly.txt"
#define INPUTFILE "data/input.txt"

// Mighty shit
// ToDo: Tilfoej flere ordklasser at sortere efter

void komma_function(int *found_nexus, int *found_rule, int tekst_count, word *wArr);
void user_prompt(char *senten_array, int *found_nexus, int *found_rule, char *user_input, int tekst_count, int i,word *wArr,int length_of_sen);

int main() {
    setlocale(LC_ALL, "da_DK.UTF-8");
    int length_tekst = 0;
    int * found_nexus;
    
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
    	printf("Ord: %s - Ordklase: %d\n", wArr[i].word_org, wArr[i].type);
    }
  

    int *found_rule = malloc(tekst_count * sizeof(int) * 8);

    rules(tekst_array, found_rule);

    found_nexus = nexus(wArr, *senten_array, tekst_count, length_tekst);
    
    for(int i = 0; i < tekst_count;i++){
        printf("\n FOUND NEXUS: %d \n",found_nexus[i]);
    }
    int b = 0;
    int length_of_sen = sizeof(senten_array)/sizeof(senten_array[0]);
    printf ("\nLEN::%d",length_of_sen);
    char *user_input = {0};
    user_prompt(*senten_array,found_nexus,found_rule,user_input,tekst_count,b, wArr, length_of_sen);

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
        
        } else if((found_nexus[itr+1] == 1) && (itr != tekst_count - 1)){
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




void user_prompt(char *senten_array, int *found_nexus, int *found_rule, char *user_input, int tekst_count, int i, word *wArr,int length_of_sen){
    


    for(int z = 0;z <length_of_sen;z++ ){
        int sent_l = strlen(&senten_array[z]);
        printf("Efter hvilket ord skal der v‘re komma? \n %s", senten_array[length_of_sen-1]);
        scanf(" %s", user_input);

        for(i; i < sent_l; i++ ){
            if (found_nexus[i] == 1 || found_rule[i] == 1){
                if(strcmp(wArr[i].word, user_input) == 0){
                    printf("DU HAR SAT ET RIGTIGT KOMMA + 10 POINT");
                    user_prompt(senten_array,found_nexus, found_rule, user_input, tekst_count, i, wArr,length_of_sen);
                    
                }else{
                    i = 0;
                    printf("Forkert svar pr›v igen");
                    user_prompt(senten_array,found_nexus, found_rule, user_input, tekst_count, i, wArr,length_of_sen);
                } 
            }
        }
    }

}