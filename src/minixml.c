#include "mxml.h"
#include "word.h"
#include "reader.h"
#include "utf8.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>




#define PATH_TO_XML_FILE    "data/RO12.xml" // TODO: Fix this hardcoded shit
#define PATH_TO_INPUT_FILE  "data/input.txt" // TODO: Fix me plz.

word functionBoi();



int cmpfunc (const void * a, const void * b) {
    return ( * (int* )a - *(int*)b );
}


int GetType(const char *ordklasse) {
    if (!(utf8cmp(ordklasse, "adj"))) {
        return ADJ;
    } else if (!(utf8cmp(ordklasse, "adj,præp"))) {
        return ADJ_PRÆP;
    } else if (!(utf8cmp(ordklasse, "adv"))) {
        return ADV;
    } else if (!(utf8cmp(ordklasse, "adv,konj"))) {
        return ADV_KONJ;
    } else if (!(utf8cmp(ordklasse, "adv,udråbsord"))) {
        return ADV_UDRÅBSORD;
    } else if (!(utf8cmp(ordklasse, "art"))) {
        return ART;
    } else if (!(utf8cmp(ordklasse, "artikel,talord"))) {
        return ARTIKEL_TALORD;
    } else if (!(utf8cmp(ordklasse, "flerord"))) {
        return FLERORD;
    } else if (!(utf8cmp(ordklasse, "fork"))) {
        return FORK;
    } else if (!(utf8cmp(ordklasse, "fsubj"))) {
        return FSUBJ;
    } else if (!(utf8cmp(ordklasse, "kolon"))) {
        return KOLON;
    } else if (!(utf8cmp(ordklasse, "konj"))) {
        return KONJ;
    } else if (!(utf8cmp(ordklasse, "konj,infinitivens.mærke"))) {
        return KONJ_INFINITIVENS_MÆRKE;
    } else if (!(utf8cmp(ordklasse, "lydord"))) {
        return LYDORD;
    } else if (!(utf8cmp(ordklasse, "pron"))) {
        return PRON;
    } else if (!(utf8cmp(ordklasse, "pron,talord"))) {
        return PRON_TALORD;
    } else if (!(utf8cmp(ordklasse, "prop"))) {
        return PROP;
    } else if (!(utf8cmp(ordklasse, "præfiks"))) {
        return PRÆFIKS;
    } else if (!(utf8cmp(ordklasse, "præp"))) {
        return PRÆP;
    } else if (!(utf8cmp(ordklasse, "præp,adv"))) {
        return PRÆP_ADV;
    } else if (!(utf8cmp(ordklasse, "præp,adv,konj"))) {
        return PRÆP_ADV_KONJ;
    } else if (!(utf8cmp(ordklasse, "præp,konj"))) {
        return PRÆP_KONJ;
    } else if (!(utf8cmp(ordklasse, "sb"))) {
        return SB;
    } else if (!(utf8cmp(ordklasse, "talord"))) {
        return TALORD;
    } else if (!(utf8cmp(ordklasse, "udråbsord"))) {
        return UDRÅBSORD;
    } else if (!(utf8cmp(ordklasse, "udråbsord,adj"))) {
        return UDRÅBSORD_ADJ;
    } else if (!(utf8cmp(ordklasse, "vb"))) {
        return VB;
    } else {
        return UNDEFINED;
    }
}

char *GetTypeString(wordtype t) {
    switch(t) {
        case ADJ:       return "Adjektiv (Tilægsord)";      break;
        case ADV:       return "Adverbium (Biord)";         break;
        case ART:       return "Artikel (Kendeord)";        break;
        case FLERORD:   return "Flerord (Flerord)";         break;
        case FORK:      return "Forkortelse (Forkortelse)"; break;
        case KONJ:      return "Konjunktion (Bindeord)";    break;
        case LYDORD:    return "Lydord (Lydord)";           break;
        case PRON:      return "Pronomen (Stedord)";        break;
        case PROP:      return "Proprium (Egenavn)";        break;
        case PRÆP:      return "Præposition (Forholdsord)"; break;
        case SB:        return "Substantiv (Navneord)";     break;
        case TALORD:    return "Numerale (Talord)";         break;
        case UDRÅBSORD: return "Interjektion (Udråbsord)";  break;
        case VB:        return "Verbum (Udsagnsord)";       break;
        default:        return "Tisboi";                    break;
    }
}

int main() {
    word w_temp;
    int tekst_count = 0;
    int length_tekst = 0;
    char ** tekst_array = read_from_file(PATH_TO_INPUT_FILE, &length_tekst, " \n");

    while (tekst_array[tekst_count] != NULL) {
        tekst_count ++;
    }

    // for (int i = 0; i < tekst_count; i++) {
    //     utf8lwr(tekst_array[i]);
    // }

    word wArr[tekst_count];
    
    FILE *fp;
    fp = fopen(PATH_TO_XML_FILE, "r");
    mxml_node_t *tree;
    tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);    
    
    for (int i = 0; i < tekst_count; i++) {
        
        w_temp = functionBoi(tekst_array[i], tree);
        // printf("ORD: %s\n", w_temp.word);
        // printf("KLASSE: %s\n\n", GetTypeString(w_temp.type));


        strcpy(wArr[i].word, w_temp.word);
        wArr[i].type = w_temp.type;
    }

    // for (int i = 0; i < tekst_count; i++) {
    //     printf("ORD #%d: %s\n", i, wArr[i].word);
    //     printf("KLASSE #%d: %u\n", i, wArr[i].type);
    // }

    fclose(fp);

    return 0;
}

word functionBoi(char *input, mxml_node_t *tree) {
    word w1;
    w1.type = UNDEFINED;

    mxml_node_t *node;
    // word a[50];
    int ff_count = 0; // Fuldform Count
    int options[15];

    int wl = strlen(input);
    if (input[wl-1] == '.') {
            input[wl-1] = '\0';
    }

    char temp_w[50];
    strcpy(temp_w, input);
    utf8lwr(input);

    int nummer = 0;
    for (node = mxmlFindElement(tree, tree, "ff", NULL, NULL, MXML_DESCEND); node != NULL; node = mxmlFindElement(node, tree, "ff", NULL, NULL, MXML_DESCEND)) {
        const char *tekst = mxmlGetText(node, 0);
        const char *att = mxmlElementGetAttr(node, "ordklasse");

        if (!(utf8cmp(tekst, input)) && (GetType(att) != FLERORD)){
            options[ff_count] = GetType(att);
            strcpy(w1.word, temp_w);
            if (w1.type == GetType(att)) {
                w1.type = GetType(att);
            } else if (w1.type == UNDEFINED) {
                w1.type = GetType(att); 
            }   

            ff_count++;  
        }
        nummer++;
    }

    if (ff_count > 1) {
        
        qsort(options, ff_count, sizeof(int), cmpfunc);
        int x = 0;

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
        

        printf("%d\n", ff_count);


        if (ff_count > 1) {
            // printf("Flere ordklasser for ordet: \"%s\", vælg venligst en: \n", w1.word);
            // for (int q = 0; q < ff_count; q++) {
            //     printf("(%d) %s\n", q+1, GetTypeString(options[q]));
            // }
            
            int valg = 0;
            char *end;
            char buf[LINE_MAX];

            while (valg <= 0 || valg > ff_count/*' || (isdigit(valg) == 0)*/) {
                
                printf("Flere ordklasser for ordet: \"%s\", vælg venligst en: \n", w1.word);
                
                for (int q = 0; q < ff_count; q++) {
                    printf("(%d) %s\n", q+1, GetTypeString(options[q]));
                }
                printf(">");
                

                // int n;
                // do {
                //     if (!fgets(buf, sizeof buf, stdin)) {
                //         break;
                //     }

                //     // remove \n
                //     buf[strlen(buf) - 1] = 0;

                //     n = strtol(buf, &end, 10);

                // } while (end != buf + strlen(buf));


                int n;
                if (!fgets(buf, sizeof buf, stdin)) {
                    break;
                }
                // remove \n
                buf[strlen(buf) - 1] = 0;
                n = strtol(buf, &end, 10);
                printf("%d\n", n);
                valg = n;
                
            }

            w1.type = options[valg-1];

        }   else {
                strcpy(w1.word, temp_w);
                w1.type = options[0];
        }
 
    } 

    else if (ff_count == 0) {
        strcpy(w1.word, temp_w);
        w1.type = PROP;
    }

    return w1;
}