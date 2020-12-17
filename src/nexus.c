#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"


#define UDSAGNSLED 1
#define GRUNDLED 2
#define KONJUNKTION 3
void user_prompt(int *found_nexus, int *found_rule, char *user_input[], int tekst_count, int i, int m, word *wArr);
int * nexus(word *wArr, int tekst_count, int length_tekst, int *found_rule){
    int i = 0;
    int count_grundled = 0;
    int count_udsagnsled = 0;
    int count_konjunktion = 0;


    printf("\nTekst:  %d\n", tekst_count);
    int * found_nexus = malloc(tekst_count* sizeof(int) * 8);

    int sentence_words[tekst_count]; // S‘tningsled ( 1 = Udsagnsled, 2 = Grundled, 3 = Bindeord)

    //Loop
    int x = 0;
    int first = 0;
    for(i = 0; i < tekst_count; i++){
        
        int wl = strlen(wArr[i].word_org);

        //Finde grundled
        //Starter med stedord og navneord og egennavne
        if(wArr[i].type == PRON || wArr[i].type == SB || wArr[i].type == PROP) {
            if (count_grundled == 0 && i > 0 && wArr[i-1].type != PRAEP) {
                sentence_words[i] = GRUNDLED;
                count_grundled++;
            } else if (count_konjunktion > 0 && count_udsagnsled > 0 && !(wArr[i].word_org[wl-1] == '.')) {
                sentence_words[i] = GRUNDLED;
                count_grundled++;
            } 
        }        

        //Finde udsagnsled
        else if(wArr[i].type == VB){
            if (count_udsagnsled == 0) {
                sentence_words[i] = UDSAGNSLED;
                count_udsagnsled++;
            } else if (count_konjunktion > 0 && count_grundled > 0) {
                sentence_words[i] = UDSAGNSLED;
                count_udsagnsled++;
            } 
        } 
        
        // Finde konjunktion
        else if(wArr[i].type == KONJ){
            sentence_words[i] = KONJUNKTION;
            count_konjunktion++;
            if (count_grundled > 0 && count_udsagnsled > 0) { //Første del er god nok
                first++;
                count_grundled = 0;
                count_udsagnsled = 0;
            }
        } 


        // Default
        else {
            sentence_words[i] = 0;
        }


        printf("Grundled: %d - %s\n", count_grundled, wArr[i].word_org);
        printf("Udsagnsled: %d - %s\n", count_udsagnsled, wArr[i].word_org);   
        if (wArr[i].word_org[wl-1] == '.') { // Tjekker for punktum
            // Finde NEXUS og finde plads til komma (konjunktion)
            while (x < i) {
                printf("GRUNDLED: %d - %s\n", count_grundled, wArr[x].word_org);
                printf("UDSAGNSLED: %d - %s\n", count_udsagnsled, wArr[x].word_org);
                if(count_grundled > 0 && count_udsagnsled > 0 && sentence_words[x] == KONJUNKTION && first == count_konjunktion){
                    found_nexus[x] = 1;

                } else {
                    found_nexus[x] = 0;
                }
                x++;
            }
            count_grundled = 0;
            count_udsagnsled = 0;
            count_konjunktion = 0;
            first = 0;  
        }
     
    }
      
    for (int i = 0; i < tekst_count; i++)
    {
        printf("%s", wArr[i].word_org);

        if (sentence_words[i] == 2)
        {
            printf("(X) ");
        }
        else if (sentence_words[i] == 1)
        {
            printf("(O) ");
        }
        else
        {
            printf(" ");
        }

        int v = strlen(wArr[i].word_org);
        if (wArr[i].word_org[v - 1] == '.')
        {
            printf("INDSAET KOMMA EFTER ORDET \n");

            printf("\n");
        }
    }
    char **user_input = malloc(50 * sizeof(char *));
    i = 0;
    int m = 0;
    user_prompt(found_nexus, found_rule, user_input, tekst_count, i, m, wArr);
    return found_nexus;
}

void user_prompt(int *found_nexus, int *found_rule, char *user_input[], int tekst_count, int i, int m, word *wArr)
{
    int forkert_svar = 0;
    // int c = sizeof(wArr->word_org) / sizeof(wArr[0].word_org);
    for (int z = 0; z < 10; z++)
    {
        printf("Efter hvilket ord skal der v‘re komma? \n");

        for (int x = m; x < tekst_count; x++)
        {
            int v = strlen(wArr[x].word_org);
            printf("%s ", wArr[x].word_org);
            if (wArr[x].word_org[v - 1] == '.')
            {
                x++;
                m = x;
                break;
            }
        }
        printf("\n");
        scanf("%s", user_input[z]);
        printf("%s \n", user_input[z]);
        for (int b = i; b < m; b++)
        {
            forkert_svar = 0;
            for (int n = 0; n < tekst_count; n++)
            {
                printf("%d\n", forkert_svar);
                if (found_nexus[n] == 1 || found_rule[n] == 1)
                {
                    if (strcmp(wArr[b].word_org, user_input[z]) == 0)
                    {

                        printf("DU HAR SAT ET RIGTIGT KOMMA + 10 POINT \n");
                        break;
                        // user_prompt(found_nexus, found_rule, user_input, tekst_count, i, m, wArr);
                    }
                    else
                    {
                        forkert_svar++;
                        // printf("Forkert svar pr›v igen \n");
                        // user_prompt(found_nexus, found_rule, user_input, tekst_count, i, m, wArr);
                    }
                }
            }
            if (forkert_svar == 30)
            {
                printf("Forkert svar pr›v igen \n");
                break;
            }
        }
    }
}