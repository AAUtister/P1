#include "reader.h"
#include "word.h"
#include "rules.h"
#include "minixml.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "utf8.h"
#include "nexus.h"
#include "achievements.h"
#include "getch.h"
#include <limits.h>

#define INPUTFILE "data/input.txt"
#define PRINT_TIME 1

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void user_prompt(int *found_nexus, int *found_rule, int tekst_count, word *wArr, int *sentence_words);
void komma_function(int *found_nexus, int *found_rule, int tekst_count, word *wArr);
int *rule_used;

int main() {
    sleep(PRINT_TIME);
    printf("  _                                   ____        _ \n");
    sleep(PRINT_TIME);
    printf(" | |                                 |  _ \\      (_)               __       ___    \n");
    sleep(PRINT_TIME);
    printf(" | | _____  _ __ ___  _ __ ___   __ _| |_) | ___  _               /_ |     / _ \\   \n");
    sleep(PRINT_TIME);
    printf(" | |/ / _ \\| '_ ` _ \\| '_ ` _ \\ / _` |  _ < / _ \\| |        __ __  | |    | | | |  \n");
    sleep(PRINT_TIME);
    printf(" |   < (_) | | | | | | | | | | | (_| | |_) | (_) | |        \\ V /  | |  _ | |_| |  \n");
    sleep(PRINT_TIME);
    printf(" |_|\\_\\___/|_| |_| |_|_| |_| |_|\\__,_|____/ \\___/|_|         \\_/   |_| (_) \\___/   \n");
    printf("\n");
    printf("Indlæser filer...\n");
    printf("\n");
    
    //fflush(stdout);

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



    rule_used = malloc(tekst_count * sizeof(int) * 8);
    for (int i = 0; i < tekst_count; i++) rule_used[i] = 0;
    int *found_rule = malloc(tekst_count * sizeof(int) * 8);

    rules(tekst_array, found_rule, wArr, rule_used);
    
    int sentence_words[tekst_count];
    found_nexus = nexus(wArr, tekst_count, length_tekst, found_rule, sentence_words);

    komma_function(found_nexus, found_rule, tekst_count, wArr);
   
    user_prompt(found_nexus, found_rule, tekst_count, wArr, sentence_words);
    


    printf("Spillet er slut!\n");
    printf("Din highscore er lige nu: %d\n", player.ordklasse);



    /* Free memory */
    free(found_rule);
    free(found_nexus);
    free(tekst_array);
    free(wArr);

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
}

int in_menu = 0;
int menu_check;
void menu() {
    int valg = 0;
    // char *end;
    // char buf[LINE_MAX];
    printf("MENU:\n");
    printf("\t(1) EXIT MENU:\n");
    printf("\t(2) OPTIONS:\n");
    printf("\t(3) STATS:\n");
    printf("\t(4) QUIT:\n");
    while (valg != 27) {
        
        printf(">");
        
        // int n;
        // if (!fgets(buf, sizeof buf, stdin)) {
        //     break;
        // }
        
        // // remove \n
        // buf[strlen(buf) - 1] = 0;

        // n = strtol(buf, &end, 10);
        // valg = n;

        valg = getch();

        switch(valg) {
            case 27:
            case 49:
                printf("\nExited menu..\n");
                valg = 27;
                //in_menu = 0;
                break;
            case 50:
                printf("\nKOMMER SNART\n");
                break;
            case 51:
                printf("\nKommascore: %d\n", player.komma); 
                printf("Ordklassescore: %d\n", player.ordklasse);
                printf("Hjælp brugt: %d\n", player.help);

                break;
            case 52:
                printf("\nAfslutter...\n");
                exit(0);
                break;
        }
        
    }


}

void user_prompt(int *found_nexus, int *found_rule, int tekst_count, word *wArr, int *sentence_words)
{
    int m = 0, antal_sen = 0, b = 0, comma_in_sentence = 0;
    for (int i = 0; i < tekst_count; i++)
    {

        int v = strlen(wArr[i].word_org);
        if (wArr[i].word_org[v - 1] == '.' || wArr[i].word_org[v - 1] == '?' || wArr[i].word_org[v - 1] == '!')
        {
            antal_sen++;
        }
    }

    char user_input[100];
    int o = 0;
    
    for (int z = 0; z < antal_sen; z++)
    {   
        comma_in_sentence = 0;
        for (int x = b; x < tekst_count; x++) {
            int v = strlen(wArr[x].word_org);
            if (found_nexus[x] == 1 || found_rule[x] == 1) {
                comma_in_sentence = 1;
            }
            if (wArr[x].word_org[v - 1] == '.'||wArr[x].word_org[v - 1] == '?' || wArr[x].word_org[v - 1] == '!')
            {
                x++;
                b = x;
                break;
            }


        } 
        
        if (comma_in_sentence == 1) {
            printf("\nFør hvilket ord skal der være komma? \n\n");

            for (int x = m; x < tekst_count; x++)
            {
                int v = strlen(wArr[x].word_org);
                printf("%s", wArr[x].word_org);

                if (sentence_words[x] == 2)
                {
                    printf("(X) ");
                }
                else if (sentence_words[x] == 1)
                {
                    printf("(O) ");
                }
                else
                {
                    printf(" ");
                }

                if (wArr[x].word_org[v - 1] == '.')
                {
                    x++;
                    m = x;
                    break;
                }
            }
            
            printf("\n\n>");

           
            scanf("%s", user_input);

            if(utf8cmp(user_input, "menu") == 0) {
                menu();
                printf("\n>");
                scanf("%s", user_input);
            }

            if(utf8cmp(user_input, "help") == 0) {
                for (int n = o; n < m - 1; n++) {
                    if (found_nexus[n] == 1 || found_rule[n] == 1) {
                        int rule = rule_used[n];
                        switch(rule) {
                            case 1:
                                break;
                            case 2:
                                printf("Der sættes komma omkring indskudte sætninger.\n");
                                break;
                            case 3:
                                printf("Der sættes komma ved opremsning.\n");
                                break;
                            case 4:
                                printf("Der sættes komma, hvis somog derkan skiftes ud med hinanden.\n");
                                break;
                            case 5:
                                printf("Der sættes komma ved navnetillæg.\n");
                                break;
                            case 6:
                                printf("Der sættes komma foran fordi og men.\n");
                                break;
                            case 7:
                                printf("Der sættes komma foran at.\n");
                                break;
                            case 8:
                                //printf("\n");
                                break;
                        }
                    }
                }
                achievements(1, 2);
                printf("\n>");
                scanf("%s", user_input);
            }
            
                
            

            for (int n = o; n < m - 1; n++)
            {
                if (found_nexus[n] == 1 || found_rule[n] == 1)
                {
                    if (utf8cmp(wArr[n].word_org, user_input) == 0)
                    {

                        printf("\nDU HAR SAT ET RIGTIGT KOMMA + 10 POINT \n\n");
                        achievements(10, 1);
                        for (int q = n+1; q < m; q++) {
                             if (found_nexus[q] == 1 || found_rule[q] == 1) {
                                printf("Der er et yderligere komma! Foran hvilket ord skal næste komma være?\n");
                                printf("\n>");
                                scanf("%s", user_input);
                                if (utf8cmp(wArr[q].word_org, user_input) == 0) {
                                    printf("\nDU HAR SAT ET RIGTIGT KOMMA + 10 POINT \n\n");
                                    achievements(10, 1);
                                } else if(utf8cmp(user_input, "menu") == 0) {
                                    menu();
                                    printf("\n>");
                                    scanf("%s", user_input);
                                } else {
                                    printf("\nForkert svar 0 POINT \n\n");
                                    break;
                                }
                             }
                        }


                        break;
                    }
                    else
                    {
                        printf("\nForkert svar 0 POINT \n\n");
                        break;
                    }
                }
            }
            printf("==================================================\n");
            in_menu = 0;
            menu_check = 0;
            o = m;
        } else {
            printf("\nDer var ingen komma(er) i sætning nr. %d\n", z+1);
        }
    }
}