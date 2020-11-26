#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char nexus(char *tekst_array,char *verb_array){
    int i = 1;
    int x = 0;
    char *token;    
    const char dot [3] = ".";
    char stedord_array[200][20] = {"han","hun","jeg","hende", "hans", "deres", }; 
    char egenavn_array[200][20] = {"Karl", "Frederik", "Pelle", "Benjamin", "Mathias", "Antonio", "Johannes"};
    
    int c = 0;
    while (tekst_array[c] != EOF) {
        c++;
    }
    int word_class[c];
    //Udsagnsord
    while (x <= c-1){
        for (int i = 0; i <= 44233; i++){

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
    //Finde grundled
    //Starter med stedord
    while (x <= c-1){
        for (int i = 0; i <= 44233; i++){

            if (strcmp(tekst_array[x], stedord_array[i])){
                word_class[x] = 0;
            }
            else{
                printf("\nFundet paa , %d plads, ordet er %s", i, stedord_array[x]);
                word_class[x] = 1;
                x++;
            }
        }
        x++;
    }
    

}