#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "achievements.h"
#include "word.h"
#include "utf8.h"
#define UDSAGNSLED 1
#define GRUNDLED 2
#define KONJUNKTION 3
void user_prompt(int *found_nexus, int *found_rule, int tekst_count, word *wArr, int *sentence_words);
int *nexus(word *wArr, int tekst_count, int length_tekst, int *found_rule)
{
    int i = 0;
    int count_grundled = 0;
    int count_udsagnsled = 0;
    int count_konjunktion = 0;

    int *found_nexus = malloc(tekst_count * sizeof(int) * 8);

    int sentence_words[tekst_count]; // S‘tningsled ( 1 = Udsagnsled, 2 = Grundled, 3 = Bindeord)

    //Loop
    int x = 0;
    int first = 0;
    for (i = 0; i < tekst_count; i++)
    {

        int wl = strlen(wArr[i].word_org);

        //Finde grundled
        //Starter med stedord og navneord og egennavne
        if (wArr[i].type == PRON || wArr[i].type == SB || wArr[i].type == PROP)
        {
            if (count_grundled == 0 && i > 0 && wArr[i - 1].type != PRAEP)
            {
                sentence_words[i] = GRUNDLED;
                count_grundled++;
            }
            else if (count_konjunktion > 0 && count_udsagnsled > 0 && !(wArr[i].word_org[wl - 1] == '.'))
            {
                sentence_words[i] = GRUNDLED;
                count_grundled++;
            }
        }

        //Finde udsagnsled
        else if (wArr[i].type == VB)
        {
            if (count_udsagnsled == 0)
            {
                sentence_words[i] = UDSAGNSLED;
                count_udsagnsled++;
            }
            else if (count_konjunktion > 0 && count_grundled > 0)
            {
                sentence_words[i] = UDSAGNSLED;
                count_udsagnsled++;
            }
        }

        // Finde konjunktion
        else if (wArr[i].type == KONJ)
        {
            sentence_words[i] = KONJUNKTION;
            count_konjunktion++;
            if (count_grundled > 0 && count_udsagnsled > 0)
            { //Første del er god nok
                first++;
                count_grundled = 0;
                count_udsagnsled = 0;
            }
        }

        // Default
        else
        {
            sentence_words[i] = 0;
        }

        if (wArr[i].word_org[wl - 1] == '.')
        { // Tjekker for punktum
            // Finde NEXUS og finde plads til komma (konjunktion)
            while (x < i)
            {
                if (count_grundled > 0 && count_udsagnsled > 0 && sentence_words[x] == KONJUNKTION && first == count_konjunktion)
                {
                    found_nexus[x] = 1;
                }
                else
                {
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

    user_prompt(found_nexus, found_rule, tekst_count, wArr, sentence_words);
    return found_nexus;
}

void user_prompt(int *found_nexus, int *found_rule, int tekst_count, word *wArr, int *sentence_words)
{
    int m = 0, antal_sen = 0;
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
        printf("Før hvilket ord skal der være komma? \n\n");

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
        
        for (int n = o; n < m - 1; n++)
        {
            if (found_nexus[n] == 1 || found_rule[n] == 1)
            {
                if (utf8cmp(wArr[n].word_org, user_input) == 0)
                {

                    printf("DU HAR SAT ET RIGTIGT KOMMA + 10 POINT \n\n");
                    achievements(10);
                    break;
                }
                else
                {
                    printf("Forkert svar 0 POINT \n\n");
                    break;
                }
            }
        }
        printf("==================================================\n");
        o = m;
    }
}