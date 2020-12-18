#include "mxml.h"
#include "word.h"
#include "reader.h"
#include "achievements.h"
#include "utf8.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>


#define PATH_TO_XML_FILE    "data/RO12.xml"
#define PATH_TO_INPUT_FILE  "data/input.txt"

typedef struct {
    wordtype type[28];      // Array af mulige ordklasser for et ord.
    int count;
} options;

word functionBoi();
options returnClasses();
void oArr_maker();
void promptType();
char getche(void);
int cmpfunc (const void * a, const void * b) {
    return ( * (int* )a - *(int*)b );
}

int GetType(const char *ordklasse) {
    if (!(utf8cmp(ordklasse, "adj"))) {
        return ADJ;
    } else if (!(utf8cmp(ordklasse, "adj,præp"))) {
        return ADJ_PRAEP;
    } else if (!(utf8cmp(ordklasse, "adv"))) {
        return ADV;
    } else if (!(utf8cmp(ordklasse, "adv,konj"))) {
        return ADV_KONJ;
    } else if (!(utf8cmp(ordklasse, "adv,udråbsord"))) {
        return ADV_UDRAABSORD;
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
        return KONJ_INFINITIVENS_MAERKE;
    } else if (!(utf8cmp(ordklasse, "lydord"))) {
        return LYDORD;
    } else if (!(utf8cmp(ordklasse, "pron"))) {
        return PRON;
    } else if (!(utf8cmp(ordklasse, "pron,talord"))) {
        return PRON_TALORD;
    } else if (!(utf8cmp(ordklasse, "prop"))) {
        return PROP;
    } else if (!(utf8cmp(ordklasse, "præfiks"))) {
        return PRAEFIKS;
    } else if (!(utf8cmp(ordklasse, "præp"))) {
        return PRAEP;
    } else if (!(utf8cmp(ordklasse, "præp,adv"))) {
        return PRAEP_ADV;
    } else if (!(utf8cmp(ordklasse, "præp,adv,konj"))) {
        return PRAEP_ADV_KONJ;
    } else if (!(utf8cmp(ordklasse, "præp,konj"))) {
        return PRAEP_KONJ;
    } else if (!(utf8cmp(ordklasse, "sb"))) {
        return SB;
    } else if (!(utf8cmp(ordklasse, "talord"))) {
        return TALORD;
    } else if (!(utf8cmp(ordklasse, "udråbsord"))) {
        return UDRAABSORD;
    } else if (!(utf8cmp(ordklasse, "udråbsord,adj"))) {
        return UDRAABSORD_ADJ;
    } else if (!(utf8cmp(ordklasse, "vb"))) {
        return VB;
    } else {
        return UNDEFINED;
    }
}

char *GetTypeString(wordtype t) {
    switch(t) {
        case ADJ:                          return "Adjektiv (Tilægsord)";                                               break;
        case ADJ_PRAEP:                    return "Adjektiv, Præposition (Tillægsord, Forholdsord)";                    break;
        case ADV:                          return "Adverbium (Biord)";                                                  break;
        case ADV_KONJ:                     return "Adverbium, Konjunktion (Biord, Bindeord)";                           break;
        case ADV_UDRAABSORD:               return "Adverbium, Udråbsord (Biord, Udråbsord)";                            break;
        case ART:                          return "Artikel (Kendeord)";                                                 break;
        case ARTIKEL_TALORD:               return "Artikel, Talord (Artikel, Talord)";                                  break;
        case FLERORD:                      return "Flerord (Flerord)";                                                  break;
        case FORK:                         return "Forkortelse (Forkortelse)";                                          break;
        case FSUBJ:                        return "Fsubj (Formelt subjekt)";                                            break;
        case KOLON:                        return "Kolon (Kolon)";                                                      break;
        case KONJ:                         return "Konjunktion (Bindeord)";                                             break;
        case KONJ_INFINITIVENS_MAERKE:     return "Konjunktion, Infinitiv (Navneord, Navnemåde)";                       break;
        case LYDORD:                       return "Lydord (Lydord)";                                                    break;
        case PRON:                         return "Pronomen (Stedord)";                                                 break;
        case PRON_TALORD:                  return "Pronomen, Talord (Stedord, Talord)";                                 break;
        case PROP:                         return "Proprium (Egenavn)";                                                 break;
        case PRAEFIKS:                     return "Præfiks (Præfiks)";                                                  break;
        case PRAEP:                        return "Præposition (Forholdsord)";                                          break;
        case PRAEP_ADV:                    return "Præposition, Adverbium (Forholdsord, Biord)";                        break;
        case PRAEP_ADV_KONJ:               return "Præposition, Adverbium, Konjunktion (Forholdsord, Biord, Bindeord)"; break;
        case PRAEP_KONJ:                   return "Præposition, Konjunktion (Forholdsord, Bindeord)";                   break;
        case SB:                           return "Substantiv (Navneord)";                                              break;
        case TALORD:                       return "Numerale (Talord)";                                                  break;
        case UDRAABSORD:                   return "Interjektion (Udråbsord)";                                           break;
        case UDRAABSORD_ADJ:               return "Udråbsord, Adjektiv (Udråbsord, Tillægsord)";                        break;
        case VB:                           return "Verbum (Udsagnsord)";                                                break;
        default:                           return "Udefineret ordklasse";                                               break;
    }
}

void wArr_maker(char ** tekstArr, word * wArr) {
    int wordCount = 0;
	options * oArr;
    oArr = (options *) calloc(sizeof(oArr), sizeof(options) + 1000);

    while (tekstArr[wordCount] != NULL) {
        wordCount ++;
    }

    FILE *fp = fopen(PATH_TO_XML_FILE, "r");
    mxml_node_t *tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);    
    //printf("TEST TEST TEST TEST TEST\n");
	char * input;

	for (int i = 0; i < wordCount; i++) { 
	    int wl = strlen(tekstArr[i]);
	    input = malloc(wl * sizeof(char) + 1000);
	    strcpy(input, tekstArr[i]);
	    strcpy(wArr[i].word_org, tekstArr[i]);
	    if (tekstArr[i][wl-1] == '.') {
            input[wl-1] = '\0';
    	}
        strcpy(wArr[i].word, input);
        free(input);
	}
	

	oArr_maker(tekstArr, oArr, wordCount, tree);
    printf("Filerne blev indlæst succesfuldt!\n\n");
	// REGLER
	for (int i = 0; i < wordCount; i++) {
		
        // Hvis der er flere ordklasser
        if (oArr[i].count > 1) {
			if (i > 0 && wArr[i-1].type == PROP) {
				if (i < wordCount && wArr[i+1].type == SB) {
					wArr[i].type = VB;
				} else {
					promptType(&wArr[i], &oArr[i]);
				}
			} else {
				promptType(&wArr[i], &oArr[i]);
			}

        // Hvis der er 1 eller færre ordklasser
		} else {
            
            if (utf8isupper(wArr[i].word_org[0]) && (oArr[i].type[0] == SB)) {
                int wl = strlen(wArr[i-1].word_org);
                if (i > 0 && (wArr[i-1].word_org[wl-1]) != '.' ) {
                    wArr[i].type = PROP;
                }
            } else {
                wArr[i].type = oArr[i].type[0];
            }
        }
	}

    fclose(fp);
}

void promptType(word * WP, options * OP) {
        int valg = 0;
        // char *end;
        // char buf[LINE_MAX];
        while (valg <= 0 || valg > OP->count) {
            
            printf("\nFlere ordklasser for ordet: \"%s\", vælg venligst en: \n", WP->word);
            
            for (int q = 0; q < OP->count; q++) {
                printf("(%d) %s\n", q+1, GetTypeString(OP->type[q]));
            }
            printf(">");
            
            // int n;
            // if (!fgets(buf, sizeof buf, stdin)) {
            //     break;
            // }
            
            // // remove \n
            // buf[strlen(buf) - 1] = 0;

            // n = strtol(buf, &end, 10);
            // valg = n;
            valg = getche() - 48;

            
        }

        WP->type = OP->type[valg-1];

        achievements(1, ORDKLASSE);        	
}

// Giver et array af "Options" structs tilbage
void oArr_maker(char ** tekstArr, options * oArr, int wc, mxml_node_t * tree) {
	options o_temp;
	for (int i = 0; i < wc; i++) { //Køre igennem hvert ord
		o_temp = returnClasses(tekstArr[i], tree); // Får klasse-array og count	

		// Filtrerer for dupliketter
	    if (o_temp.count > 1) {
		    qsort(o_temp.type, o_temp.count, sizeof(int), cmpfunc);
		    for(int i = 0; i < o_temp.count; i++) {
		        for(int j = i+1; j < o_temp.count; ) {
		            if(o_temp.type[j] == o_temp.type[i]) {
		                for(int k = j; k < o_temp.count; k++) {
		                    o_temp.type[k] = o_temp.type[k+1];
		                }
		                o_temp.count--;
		            }
		            else {
		                j++;
	            	}	
	        	}
	    	}
    	} else if (o_temp.count == 0) {
    		o_temp.type[0] = PROP;
    		o_temp.count = 1;
    	}

		// Indsætter i oArr
		for (int y = 0; y < o_temp.count; y++) {
			oArr[i].type[y] = o_temp.type[y];
		}
		oArr[i].count = o_temp.count;
	}
}

options returnClasses(char *input, mxml_node_t *tree) {
    options o;
    mxml_node_t *node;
    o.count = 0;
    int wl = strlen(input);
    if (input[wl-1] == '.') {
            input[wl-1] = '\0';
    }
    utf8lwr(input);
    
    for (node = mxmlFindElement(tree, tree, "ff", NULL, NULL, MXML_DESCEND); node != NULL; node = mxmlFindElement(node, tree, "ff", NULL, NULL, MXML_DESCEND)) {
        const char *tekst = mxmlGetText(node, 0);
        const char *att = mxmlElementGetAttr(node, "ordklasse");

        if (!(utf8cmp(tekst, input)) && (GetType(att) != FLERORD)){
            switch(GetType(att)) {
                case ADJ_PRAEP:
                    o.type[o.count++] = ADJ;
                    o.type[o.count++] = PRAEP;
                    break;
                case ADV_KONJ:
                    o.type[o.count++] = ADV;
                    o.type[o.count++] = KONJ;
                    break;
                case ADV_UDRAABSORD:
                    o.type[o.count++] = ADV;
                    o.type[o.count++] = UDRAABSORD;
                    break;
                case ARTIKEL_TALORD:
                    o.type[o.count++] = ART;
                    o.type[o.count++] = TALORD;
                    break;
                case PRON_TALORD:
                    o.type[o.count++] = PRON;
                    o.type[o.count++] = TALORD;
                    break;
                case PRAEP_ADV:
                    o.type[o.count++] = PRAEP;
                    o.type[o.count++] = ADV;
                    break;
                case PRAEP_ADV_KONJ:
                    o.type[o.count++] = PRAEP;
                    o.type[o.count++] = ADV;
                    o.type[o.count++] = KONJ;
                    break;
                case UDRAABSORD_ADJ:
                    o.type[o.count++] = UDRAABSORD;
                    o.type[o.count++] = ADJ;
                    break;
                case KONJ_INFINITIVENS_MAERKE: // Følger default (Kun ordet "at")
                default:
                    o.type[o.count++] = GetType(att);            
                    break;  
            }
            
        }   
    }   

    return o;
}
