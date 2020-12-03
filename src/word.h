#ifndef WORD_H
#define WORD_H

typedef enum {
    VERB,   //vb-artikel
    SUB     //sb-artikel
} wordtype;

typedef struct {
    wordtype type;      //Tal som bestemmer klassen
    char word[50];      //ordet i sig selv
} word;

#endif
