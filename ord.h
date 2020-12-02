#ifndef ORD.H
#define ORD.H

typedef enum {
    VERB,   //vb-artikel
    SUB     //sb-artikel
} ordklasse;

typedef struct {
    ordklasse klasse;  //Tal som bestemmer klassen
    char ord[50];  //ordet i sig selv
} word;

#endif