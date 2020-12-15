#ifndef WORD_H
#define WORD_H

typedef enum {
	ADJ,
	ADJ_PRAEP,
	ADV,
	ADV_KONJ,
	ADV_UDRAABSORD,
	ART,
	ARTIKEL_TALORD,
	FLERORD,
	FORK,
	FSUBJ,
	KOLON,
	KONJ,
	KONJ_INFINITIVENS_MAERKE,
	LYDORD,
	PRON,
	PRON_TALORD,
	PROP,
	PRAEFIKS,
	PRAEP,
	PRAEP_ADV,
	PRAEP_ADV_KONJ,
	PRAEP_KONJ,
	SB,
	TALORD,
	UDRAABSORD,
	UDRAABSORD_ADJ,
	VB,
	UNDEFINED = -1
} wordtype;

typedef struct {
    wordtype type;      //Tal som bestemmer klassen
    char word[50];      //ordet i sig selv
    char word_org[50];
} word;

#endif
