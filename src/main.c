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
#include "gtk/gtk.h"


// TODO: Find ud af om det skal vaere hardkodet eller mulighed for begge ting
#define VERBSFILE "data/verbs_ascii_friendly.txt"
#define INPUTFILE "data/input.txt"

// Mighty shit
// ToDo: Tilfoej flere ordklasser at sortere efter

void komma_function(int *found_nexus, int *found_rule, int tekst_count, word *wArr);

// called when window is closed
void on_windowBoi_destroy() {
    gtk_main_quit();
}

int i = 0;

GtkBuilder * builder; 
GtkWidget * window;
GtkWidget *tissemand;
void on_buttonBoi_clicked() {
    
    char pik[100];
    char test[6][10] = {"penis", "diller", "tissemand", "pik", "schnell", "tisboi"};
    strcat(pik, test[i]);
    strcat(pik, "hest");
    gtk_label_set_text(GTK_LABEL(tissemand), pik);
    i++;
    if (i > 6) {
        gtk_widget_hide(window);
        gtk_main_quit();
    }
}


int main() {
    setlocale(LC_ALL, "da_DK.UTF-8");
    

    

    gtk_init(NULL, NULL);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "windowBoi.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "windowBoi"));
    gtk_builder_connect_signals(builder, NULL);

    tissemand = GTK_WIDGET(gtk_builder_get_object(builder, "tissemand"));



    g_object_unref(builder);

    gtk_widget_show(window);                



    gtk_main();




























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
