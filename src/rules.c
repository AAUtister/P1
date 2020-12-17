#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utf8.h"
#include "word.h"

#define HV_ARRAY_LEN 11

void rules(char *tekst_array[], int found_rule[], word *wArr) {

    char *hv_array[HV_ARRAY_LEN] = {"hvem", "hvad", "hvornår", "hvorfor", "hvordan", "hvor", "hvilken", "hvorfra", "hvorhen", "hvilket", "hvilke"};
    int c = 0;

    while (tekst_array[c] != NULL) {
        printf("String: %s\n", tekst_array[c]);
        c++;
    }
    printf("C: %d\n", c);


    for (int i = 0; i < c; i++) {
        
        for (int j = 0; j < HV_ARRAY_LEN; j++) {
            int ret = utf8cmp(tekst_array[i], hv_array[j]);
            if (ret == 0) {
                found_rule[i] = 1;
                break;
            }
            else {
                found_rule[i] = 0;
            }
        }

    }
    


    ////// Regel 2: Der sættes komma omkring indskudte sætninger.
    int i = 0;
    int z;
    int seneste_punktum = -1;
    int vb_test = 0;
    while (i < c) {
        // Finder næste punktum og nulstiller vb_test
        int wl = strlen(wArr[i].word_org);
        if (wArr[i].word_org[wl-1] == '.') {
            seneste_punktum = i;
            vb_test = 0;
        }

        // Sammenligner der/som med nuværende ord
        int som = utf8cmp(wArr[i].word, "som");
        int der = utf8cmp(wArr[i].word, "der");

        // Tjekker om ordet er som/der, hvorefter den tjekker om næste ord er VB
        if (som == 0 || der == 0) {
            if (wArr[i+1].type == VB) {
                // Starter ved næste sætning og tjekker om der er VB
                for (z = seneste_punktum+1; z < i; z++) {
                    if (wArr[z].type == VB) {
                        vb_test = 1;
                    }
                } 
                // Hvis der ikke var et VB, sættes første komma
                if (vb_test == 0) {
                    found_rule[i] = 1;
                    int vb_counter = 0;
                    int n = i;
                    // Her finder den næste sted at sætte komma (ved andet VB)
                    while (vb_counter <= 2) {
                        if (wArr[n].type == VB) {
                            vb_counter++;
                            if (vb_counter == 2) {
                                found_rule[n] = 1;
                            }
                        }
                        n++;
                    }
                } 
            }
        }




        i++;
    }



    /// REGEL 3: Der sættes komma ved opremsning.
    /*
    Når der kommer et substantiv:
        Tjek frem til næste punktum:
            Er der max 1 "og"/"eller":
            Er der minimum 2 substanstiver efter det første SB
    */
    for (int i = 0; i < c; i++) {
        int x = i;
        int wc = strlen(wArr[x].word_org);
        int z = i;
        int sb_check = 0;
        int oe_check = 0;

        if (wArr[i].type == SB) {
            while (wArr[x].word_org[wc-1] != '.') {
                x++;
                wc = strlen(wArr[x].word_org);
            }

            while (z < x) {
                int og = utf8cmp(wArr[z].word, "og");
                int eller = utf8cmp(wArr[z].word, "eller");

                if (og == 0 || eller == 0) {
                    oe_check++;
                }

                if (wArr[z].type == SB) {
                    sb_check++;
                }
                z++;
            }
        }

        // Der bliver tjekket om der er minimum 3 SB og at KUN 1 og/eller
        if (sb_check > 2 && oe_check == 1) {
            for (int fr = i; fr < x-1; fr++) {
                int o_next = utf8cmp(wArr[fr+1].word, "og");
                int e_next = utf8cmp(wArr[fr+1].word, "eller");
                if (wArr[fr].type == SB && o_next != 0) {
                    found_rule[fr+1] = 1;
                } else if (wArr[fr].type == SB && e_next != 0) {
                    found_rule[fr+1] = 1;
                }
                // HVIS DER ER OG/ELLER SOM NÆSTE:
                if (wArr[fr].type == SB && o_next == 0) {
                    found_rule[fr+1] = 2;
                } else if (wArr[fr].type == SB && e_next == 0) {
                    found_rule[fr+1] = 2;
                }
            }
        }
    }





    // REGEL 4: Der sættes komma, hvis somog derkan skiftes ud med hinanden.
    /*    
    Hvis ordet er som/der:
        Hvis der ikke er et HV-ord foran ordet
            Er ordet efterfulgt af adverbium ELLER verbum?
                Sæt komma foran ordet
    */
    for (int i = 0; i < c; i++) {

        int som = utf8cmp(wArr[i].word, "som");
        int der = utf8cmp(wArr[i].word, "der");
        if (som == 0 || der == 0) {
            int hv_positiv = 0;
            for (int z = 0; z < HV_ARRAY_LEN; z++) {
                int hv_test = utf8cmp(wArr[i-1].word, hv_array[z]);
                if (hv_test == 0) {
                    hv_positiv = 1;
                }
            }
            if (hv_positiv == 0) {
                if (wArr[i].type == VB || wArr[i].type == ADV) {
                    found_rule[i] = 1;
                }
            }

        }
    }




  
    // REGEL 5: Der sættes komma ved navnetillæg.
    /*
    Hvis substantiv efterfulgt af egennavn:
        Der sættes komma foran første egennavn
        Der sættes komma efter sidste efterfølgende egenavn i træk

    */
    for (int i = 0; i < c; i++) {
        int x = i;
        int wc = strlen(wArr[x].word_org);
        while (wArr[x].word_org[wc-1] != '.') {
            x++;
            wc = strlen(wArr[x].word_org);
        }

        if (wArr[i].type == SB && wArr[i+1].type == PROP) {
            int q = i+1;
            found_rule[i+1] = 1;
            while (q < x) {
                if (wArr[q].type != PROP) {
                    found_rule[q] = 1;
                }
                q++;
            }
        }
    }


// REGEL 6: Der sættes komma foran fordiog men.
    /*
    Hvis ordet er "fordi" eller "men":
        Der sættes komma foran ordet
    */
    for (int i = 0; i < c; i++) {
        int fordi_check = utf8cmp(wArr[i].word, "fordi");
        int men_check = utf8cmp(wArr[i].word, "men");
        if (fordi_check == 0 || men_check == 0) {
            found_rule[i] = 1;
        }

    }

    // REGEL 8: Der sættes komma foran at.
    /*
    Hvis ordet er at og næste ord ikke er VB:
        Der sættes komma foran at
    */

    for (int i = 0; i < c; i++) {
        int at_check = utf8cmp(wArr[i].word, "at");
        if (at_check == 0 && wArr[i+1].type != VB) {
            found_rule[i] = 1;
        }

    }


}
