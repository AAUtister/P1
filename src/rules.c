#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utf8.h"
#include "word.h"

void rules(char *tekst_array[], int found_rule[], word *wArr) {
    int x = 11;
    char *hv_array[11] = {"hvem", "hvad", "hvornår", "hvorfor", "hvordan", "hvor", "hvilken", "hvorfra", "hvorhen", "hvilket", "hvilke"};
    int c = 0;

    while (tekst_array[c] != NULL) {
        printf("String: %s\n", tekst_array[c]);
        c++;
    }
    printf("C: %d\n", c);


    for (int i = 0; i < c; i++) {
        
        for (int j = 0; j < x; j++) {
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
    


    ////// Regel 2: Der sættes komma omkringindskudtesætninger.
    int i = 0;
    int z;
    int seneste_punktum = -1;
    int vb_test = 0;
    while (i < c) {
        int wl = strlen(wArr[i].word_org);


        if (wArr[i].word_org[wl-1] == '.') {
            seneste_punktum = i;
            vb_test = 0;
        }

        int som = utf8cmp(wArr[i].word, "som");
        int der = utf8cmp(wArr[i].word, "der");

        if (som == 0 || der == 0) {
            if (wArr[i+1].type == VB) {
                for (z = seneste_punktum+1; z < i; z++) {
                    if (wArr[z].type == VB) {
                        vb_test = 1;
                    }
                } 

                if (vb_test == 0) {
                    found_rule[i] = 1;
                    int vb_counter = 0;
                    int n = i;
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
            Er der ingen verbum:
            Er der et "og"/"eller":
            Er der minimum 2 substanstiver


    */
    for (int i = 0; i < c; i++) {
        if (wArr[i].type == SB) {
            int x = i;
            int wc = strlen(wArr[x].word_org);
            while (wArr[x].word_org[wc-1] != '.') {
                x++;
                wc = strlen(wArr[x].word_org);
            }

            int z = i;
            int vb_check = 1;
            int sb_check = 0;
            int oe_check = 0;
            while (z < x) {
                if (wArr[z].type == VB){
                    vb_check = 1;
                }
                
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
            if (sb_check > 2 && vb_check == 1 && oe_check == 1) {
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
