#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "achievements.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define PRINT_TIME 1

static profile p;

int getScores(int scoretype) {
	FILE *fp = fopen("savegame.csv", "r");
	
	if (fp == NULL){
        printf("Savegame kunne ikke findes. Opretter savegame...\n");
        fp = fopen("savegame.csv", "w+");
        fprintf(fp, "%d,%d,%d,%d", 0, 0, 0, 0);
        fclose(fp);
        fp = fopen("savegame.csv", "r");
        printf("Savegame oprettet!\n");
    }

    fscanf(fp, "%d,%d,%d,%d", &p.ordklasse, &p.komma, &p.help, &p.ekstra);
    
    switch(scoretype) {
    	case ORDKLASSE:
    		return p.ordklasse;
    		break;
		case KOMMA:
			return p.komma;
			break;
		case HELP:
			return p.help;
			break;
		case EKSTRA:
			return p.ekstra;
			break;
		default:
			return 0;
			break;
    }
    
}

void achievements(int point, int scoretype) {

	FILE *fp = fopen("savegame.csv", "r");
	
	if (fp == NULL){
        printf("Savegame kunne ikke findes. Opretter savegame...\n");
        fp = fopen("savegame.csv", "w+");
        fprintf(fp, "%d,%d,%d,%d", 0, 0, 0, 0);
        fclose(fp);
        fp = fopen("savegame.csv", "r");
        printf("Savegame oprettet!\n");
    }

    fscanf(fp, "%d,%d,%d,%d", &p.ordklasse, &p.komma, &p.help, &p.ekstra);

    switch(scoretype) {
    	case ORDKLASSE: 
    		p.ordklasse = p.ordklasse + point;
    		break;
    	case KOMMA: 
    		p.komma = p.komma + point;
    		break;		
    	case HELP: 
    		p.help = p.help + point;
    		break;	
    	case EKSTRA: 
    		p.ekstra = p.ekstra + point;
    		break;
    }

	if (p.ordklasse > 0 && !(p.ordklasse % 50)) {
		printf("ACHIEVEMENT UNLOCKED - DEFINE %d ORDKLASSER!\n", p.ordklasse);
		sleep(PRINT_TIME);
		printf("           .--._.--.\n");
		sleep(PRINT_TIME);
		printf("          ( O     O )\n");
		sleep(PRINT_TIME);
		printf("          /   . .   \\\n");
		sleep(PRINT_TIME);
		printf("         .`._______.'.\n");
		sleep(PRINT_TIME);
		printf("        /(           )\\\n");
		sleep(PRINT_TIME);
		printf("      _/  \\  \\   /  /  \\_\n");
		sleep(PRINT_TIME);
		printf("   .~   `  \\  \\ /  /  '   ~.\n");
		sleep(PRINT_TIME);
		printf("  {    -.   \\  V  /   .-    }\n");
		sleep(PRINT_TIME);
		printf("_ _`.    \\  |  |  |  /    .'_ _\n");
		sleep(PRINT_TIME);
		printf(">_       _} |  |  | {_       _<\n");
		sleep(PRINT_TIME);
		printf("         '-'|/   \\|`-`\n");
	}
		
	freopen(NULL, "w+", fp);
	fprintf(fp, "%d,%d,%d,%d", p.ordklasse, p.komma, p.help, p.ekstra);
	fclose(fp);
}