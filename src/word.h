#ifndef WORD_H
#define WORD_H

typedef enum {
	ADJ,
	ADJ_PRÆP,
	ADV,
	ADV_KONJ,
	ADV_UDRÅBSORD,
	ART,
	ARTIKEL_TALORD,
	FLERORD,
	FORK,
	FSUBJ,
	KOLON,
	KONJ,
	KONJ_INFINITIVENS_MÆRKE,
	LYDORD,
	PRON,
	PRON_TALORD,
	PROP,
	PRÆFIKS,
	PRÆP,
	PRÆP_ADV,
	PRÆP_ADV_KONJ,
	PRÆP_KONJ,
	SB,
	TALORD,
	UDRÅBSORD,
	UDRÅBSORD_ADJ,
	VB,
	UNDEFINED = -1

} wordtype;

typedef struct {
    wordtype type;      //Tal som bestemmer klassen
    char word[50];      //ordet i sig selv
} word;

#endif
