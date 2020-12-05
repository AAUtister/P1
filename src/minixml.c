#include "mxml.h"
#include "word.h"
#include "reader.h"
#include "utf8.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>


#define PATH_TO_XML_FILE    "data/RO12.xml" // TODO: Fix this hardcoded shit
#define PATH_TO_INPUT_FILE  "data/input.txt" // TODO: Fix me plz.

word functionBoi();



int cmpfunc (const void * a, const void * b) {
    return ( * (int* )a - *(int*)b );
}


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
    } else if (!(strcmp(ordklasse, "flerord"))) {
        return 18;
    } else {
        return UNDEFINED;

    }
}

int main() {
    setlocale(LC_ALL, "da_DK.UTF-8");
    word w_temp;
    int tekst_count = 0;
    int length_tekst = 0;
    char ** tekst_array = read_from_file(PATH_TO_INPUT_FILE, &length_tekst, " \n");

    while (tekst_array[tekst_count] != NULL) {
        tekst_count ++;
    }

    for (int i = 0; i < tekst_count; i++) {
        utf8lwr(tekst_array[i]);
    }

    word wArr[tekst_count];
    
    FILE *fp;
    fp = fopen(PATH_TO_XML_FILE, "r");
    mxml_node_t *tree;
    tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);    
    
    for (int i = 0; i < tekst_count; i++) {
        
        w_temp = functionBoi(tekst_array[i], tree);
        printf("ORD: %s\n", w_temp.word);
        printf("KLASSE: %u\n", w_temp.type);

        strcpy(wArr[i].word, w_temp.word);
        wArr[i].type = w_temp.type;
    }

    for (int i = 0; i < tekst_count; i++) {
        printf("ORD #%d: %s\n", i, wArr[i].word);
        printf("KLASSE #%d: %u\n", i, wArr[i].type);
    }

    fclose(fp);

    return 0;
}

word functionBoi(char *input, mxml_node_t *tree) {
    word w1;
    w1.type = 0;

    mxml_node_t *node;
    // word a[50];
    int ff_count = 0; // Fuldform Count
    int options[15];

    int wl = strlen(input);
    if (input[wl-1] == '.') {
            input[wl-1] = '\0';
    }

    int nummer = 0;
    for (node = mxmlFindElement(tree, tree, "ff", NULL, NULL, MXML_DESCEND); node != NULL; node = mxmlFindElement(node, tree, "ff", NULL, NULL, MXML_DESCEND)) {
        const char *tekst = mxmlGetText(node, 0);
        const char *att = mxmlElementGetAttr(node, "ordklasse");
        

        if (!(utf8cmp(tekst, input))){
            if (GetType(att) != 18) {
                options[ff_count] = GetType(att);
                strcpy(w1.word, tekst);
                if (w1.type == GetType(att)) {
                    w1.type = GetType(att);
                } else if (w1.type == 0) {
                    w1.type = GetType(att); 
                }   

                ff_count++; 
            }
        }
        nummer++;
    }

    if (ff_count > 1) {
        
        qsort(options, ff_count, sizeof(int), cmpfunc);
        int x = 0;
        // int *arr2;
        
        // arr2 = (int*)calloc(1, size(int))


        // for (int i = 0; i < ff_count; i++) {
        //     if (options[i] == 18) {
        //         continue;
        //     }
        //     for (int j = i + 1; j < ff_count; j++) {
        //         if (i == ff_count-1) {
        //             x++;
        //             arr2 = (int*)calloc(x, sizeof(int));
        //             arr2[x-1] = options[i];

        //         } else if (options[i] != options[j]) {
        //             x++;
        //             arr2 = (int*)calloc(x, sizeof(int));
        //             arr2[x-1] = options[i];
        //         }
        //     }
        // }

        for(int i = 0; i < ff_count; i++) {
            for(int j = i+1; j < ff_count; ) {
                if(options[j] == options[i]) {
                    for(int k = j; k < ff_count; k++) {
                        options[k] = options[k+1];
                    }
                    ff_count--;
                }
                else {
                    j++;
                }
            }
        }
        
        if (ff_count > 1) {
            for (int q = 0; q < ff_count; q++) {
                printf("Option: %d\n", options[q]);
            }
            printf("Flere ordklasse for ordet: %s, vælg venligst en: \n", w1.word);
            scanf("%d", &w1.type);
        }   else {
                strcpy(w1.word, input);
                w1.type = options[0];
        }
 
    } 

    else if (ff_count == 0) {
        strcpy(w1.word, input);
        w1.type = options[0];
    }

    return w1;
}