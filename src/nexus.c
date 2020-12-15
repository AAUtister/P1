#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
#include "sen_splitter.h"

int * nexus(word *wArr, char *senten_array, int tekst_count){
    int i = 0;
    int count_grundled = 0;
    int count_udsagnsled = 0;

    printf("\nTekst:  %d\n", tekst_count);
    int * found_nexus = malloc(tekst_count* sizeof(int) * 8);

    int sentence_words[tekst_count]; // S‘tningsled ( 1 = Udsagnsled, 2 = Grundled, 3 = Bindeord)
    
    //Finde udsagnsled
    for(i = 0; i < tekst_count; i++){
        if(wArr[i].type == VB){
            sentence_words[i] = 1;
            count_udsagnsled++;
        }
        else{
            sentence_words[i] = 0;
        }
        
    }
    //Finde grundled
    //Starter med stedord og navneord
    for(i = 0; i < tekst_count; i++){
        if(wArr[i].type == PRON || wArr[i].type == SB){
            sentence_words[i] = 2;
            count_grundled ++;
            break;
        }
    }   
    int a = 0;
    for(i = 0; i < tekst_count; i++){
        if(wArr[i].type == KONJ){
            sentence_words[i] = 3;
            a = i;
        }
        if(sentence_words[i] == 3){
            for( i = a; a < tekst_count; i++){
                if(wArr[i].type == PRON || wArr[i].type == SB){
                sentence_words[i] = 2;
                count_grundled ++;
                break;
                }
            } 
            
        }
    }
    for(i = 0; i < tekst_count;i++){
        if(count_grundled > 1 && count_udsagnsled > 1 && sentence_words[i] == 3){
            found_nexus[i-1] = 1;

        }
        else{
            found_nexus[i] = 0;
        }
    }
     
    return found_nexus;
}
