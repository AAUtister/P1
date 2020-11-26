#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD

char **rules(char tekst_array[])
=======
/*
char **rules(char text_array)
>>>>>>> 3143de5f4d679d67b2fca39b52064237818b7043
{
    char hv_array[10][14] = {"hvem", "hvad", "hvornaar", "hvordan", "hvor", "hvilken", "hvorfra", "hvorhen", "hvilket", "hvilke"};
    int c = 0, x = 0;

    while (&tekst_array[c] != NULL)
    {
        c++;
    }

    char **found_rule = malloc(10 * sizeof(char *));
    while (x <= c - 1)
    {

        for (int i = 0; i <= c; i++)
        {

<<<<<<< HEAD
            if (strcmp(&tekst_array[x], hv_array[i]))
            {
                found_rule[x] = 0;
            }
            else
            {
                printf("\nFundet paa , %d plads, ordet er %s", i, hv_array[x]);
                found_rule[x] = 1;
=======
			if (strcmp(tekst_array[x], verb_array[i]))
			{
				found[x] = 0;
			}
			else
			{
				printf("\nFundet paa , %d plads, ordet er %s", i, tekst_array[x]);
				binary_shit[x] = 1;
				x++;
			}
		}
		x++;
	}
    return hv_array;
}
 */








char nexus(char *tekst_array,char *verb_array){
    int i = 1;
    int x = 0;
    char *token;    
    const char dot [3] = ".";


    //Deler array op i s‘tninger - delt med punktum.
    token = strtok(tekst_array,dot);
    while(token != NULL) {
        char *tok = calloc(sizeof(token), sizeof(char));
        strcpy(tok, token);
        tekst_array[i++] = tok;
        token = strtok(NULL, dot);
    };
	int sentence_count = i;
	for(int i=0;i<=sentence_count;i++){
		printf("S‘tning: %s",tekst_array[i]);
	}
	int c = 0;
    while (tekst_array[c] != NULL) {
        c++;
    }
	 int word_class[c];
	//Udsagnsled 
    while (x <= c-1){
        for (int i = 0; i <= 44233; i++){

            if (strcmp(tekst_array[x], verb_array[i])){
                word_class[x] = 0;
            }
            else{
                printf("\nFundet paa , %d plads, ordet er %s", i, tekst_array[x]);
                word_class[x] = 1;
>>>>>>> 3143de5f4d679d67b2fca39b52064237818b7043
                x++;
            }
        }
        x++;
    }
<<<<<<< HEAD
    return found_rule;
=======
	
>>>>>>> 3143de5f4d679d67b2fca39b52064237818b7043
}