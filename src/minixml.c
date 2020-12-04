#include "mxml.h"
#include "word.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"
#include <ctype.h>
#include <locale.h>
#include <wchar.h>

#define PATH_TO_XML_FILE    "data/RO12.xml" // TODO: Fix this hardcoded shit
#define PATH_TO_INPUT_FILE  "data/input.txt" // TODO: Fix me plz.

word functionBoi();

int GetType(const char *ordklasse) {
    if (!(strcmp(ordklasse, "adj"))) {
        return 16;
    } else if (!(strcmp(ordklasse, "adv"))) {
        return 12;
    } else if (!(strcmp(ordklasse, "art"))) {
        return 17;
    } else if (!(strcmp(ordklasse, "fork"))) {
        return 3;
    } else if (!(strcmp(ordklasse, "kolon"))) {
        return 4;
    } else if (!(strcmp(ordklasse, "konj"))) {
        return 5;
    } else if (!(strcmp(ordklasse, "lydord"))) {
        return 6;
    } else if (!(strcmp(ordklasse, "pron"))) {
        return 7;
    } else if (!(strcmp(ordklasse, "proprium"))) {
        return 8;
    } else if (!(strcmp(ordklasse, "præfiks"))) {
        return 9;
    } else if (!(strcmp(ordklasse, "præp"))) {
        return 10;
    } else if (!(strcmp(ordklasse, "romertal"))) {
        return 11;
    } else if (!(strcmp(ordklasse, "sb"))) {
        return SUB;
    } else if (!(strcmp(ordklasse, "talord"))) {
        return 13;
    } else if (!(strcmp(ordklasse, "udråbsord"))) {
        return 14;
    } else if (!(strcmp(ordklasse, "vb"))) {
        return 15;
    } else {
        return UNDEFINED;

    }
}

int main() {
    setlocale(LC_ALL, "da_DK.UTF-8");
    word w_temp;
    int tekst_count = 0;
    int length_tekst = 0;
    char ** tekst_array = read_from_file("tekst1.txt", &length_tekst, " \n");

    while (tekst_array[tekst_count] != NULL) {
        tekst_count ++;
    }

    for (int i = 0; i < tekst_count; i++) {
        utf8lwr(tekst_array[i]);
    }

    

    printf("FREDERIK MED SMÅT: %s\n", tekst_array[10]);


    word wArr[tekst_count];

    printf("%d\n", tekst_count);
    
    for (int i = 0; i < tekst_count; i++) {
        
        w_temp = functionBoi(tekst_array[i], i);
        printf("ORD: %s\n", w_temp.word);
        printf("KLASSE: %u\n", w_temp.type);

        strcpy(wArr[i].word, w_temp.word);
        wArr[i].type = w_temp.type;
    }


    for (int i = 0; i < tekst_count; i++) {
        printf("ORD #%d: %s\n", i, wArr[i].word);
        printf("KLASSE #%d: %u\n", i, wArr[i].type);
    }





    return 0;



}

word functionBoi(char *input, int tree_test) {
    printf("INPUT: %s\n", input);
    word w1;
    w1.type = 0;
    FILE *fp;
    fp = fopen("RO12.xml", "r");
    mxml_node_t *tree;
    if (tree_test == 0) {
        tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);    
    }
    fclose(fp);

    mxml_node_t *node;
    // word a[50];
    int ff_count = 0; // Fuldform Count
    int options[15];

    int wl = strlen(input);
        printf("%d\n", wl);
        if (input[wl-1] == '.') {
            input[wl-1] = '\0';
            printf("PUNKTUM PUNKTUM PUNKTUM: %s\n", input);
    }


    for (node = mxmlFindElement(tree, tree, "ff", NULL, NULL, MXML_DESCEND); node != NULL; node = mxmlFindElement(node, tree, "ff", NULL, NULL, MXML_DESCEND)) {
        const char *tekst = mxmlGetText(node,0);
        const char *att = mxmlElementGetAttr(node, "ordklasse");
        

        if (!(strcmp(tekst, input))){
            options[ff_count] = GetType(att);
            strcpy(w1.word, tekst);
            if (w1.type == GetType(att)) {
                w1.type = GetType(att);
            } else if (w1.type == 0) {
                w1.type = GetType(att);    
            } else if (ff_count == 0) {
                // i++;
            } else {
                // i++;
            }  
            ff_count++; 
        } 
    }

    if (ff_count > 1) {
        for (int q = 0; q < ff_count; q++) {
        printf("Option: %d\n", options[q]);
        }
        printf("Flere ordklasse for ordet: %s, vælg venligst en: \n", w1.word);
        scanf("%d", &w1.type);
    } else if (ff_count == 0) {
        options[ff_count] = 69;
        strcpy(w1.word, input);
        w1.type == 69;
        ff_count++;
    }

    return w1;
}