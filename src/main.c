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
#include "gtk/gtk.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#define INPUTFILE "data/input.txt"

void user_prompt(int *found_nexus, int *found_rule, int tekst_count, word *wArr, int *sentence_words);
void komma_function(int *found_nexus, int *found_rule, int tekst_count, word *wArr);
void on_windowBoi_destroy() {
    gtk_main_quit();
}
GtkBuilder * builder; 
GtkWidget * window;
GtkWidget * loading;
GtkWidget * popup;

void on_dansk_clicked() {
    //sleep(1);
    gtk_widget_hide(window);
    gtk_main_quit();
}

void on_norsk_clicked() {
    for (int i = 0; i < 5; i++) {
        system("xdg-open https://www.youtube.com/watch?v=oHg5SJYRHA0");
    }
}


int main() {
    
    // UI code
    gtk_init(NULL, NULL);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "windowBoi.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "windowBoi"));
    loading = GTK_WIDGET(gtk_builder_get_object(builder, "loadingBoi"));

    popup = GTK_WIDGET(gtk_builder_get_object(builder, "dialog"));

    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    //gtk_widget_show(loading);
    gtk_widget_show(window);                
    gtk_main();




    // Standard code
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

    int *found_rule = malloc(tekst_count * sizeof(int) * 8);

    rules(tekst_array, found_rule, wArr);
    
    int sentence_words[tekst_count];
    found_nexus = nexus(wArr, tekst_count, length_tekst, found_rule, sentence_words);

    komma_function(found_nexus, found_rule, tekst_count, wArr);
   
    user_prompt(found_nexus, found_rule, tekst_count, wArr, sentence_words);

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
            if (wArr[x].word_org[v - 1] == '.')
            {
                x++;
                b = x;
                break;
            }


        } 
        
        if (comma_in_sentence == 1) {
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
                        achievements(10, 1);
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
        } else {
            printf("Der var ingen komma(er) i sætning nr. %d\n", z+1);
        }
    }
}