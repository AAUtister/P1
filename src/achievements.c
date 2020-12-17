#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

void achievements(int point, int scoretype) {
	typedef struct {
		int ordklasse;
		int komma;
		int test;
		int ekstra;

	} profile;

	FILE *fp = fopen("savegame.csv", "r");
	
	if (fp == NULL){
        printf("Savegame kunne ikke findes. Opretter savegame...\n");
        fp = fopen("savegame.csv", "w+");
        fprintf(fp, "%d,%d,%d,%d", 0, 0, 0, 0);
        fclose(fp);
        fp = fopen("savegame.csv", "r");
        printf("Savegame oprettet!\n");
    }

    profile player;

    fscanf(fp, "%d,%d,%d,%d", &player.ordklasse, &player.komma, &player.test, &player.ekstra);

    switch(scoretype) {
    	case 0: 
    		player.ordklasse = player.ordklasse + point;
    		break;
    	case 1: 
    		player.komma = player.komma + point;
    		break;		
    	case 2: 
    		player.test = player.test + point;
    		break;	
    	case 3: 
    		player.ekstra = player.ekstra + point;
    		break;
    }

    

	
	if (player.ordklasse > 0 && !(player.ordklasse % 50)) {
		printf("ACHIEVEMENT UNLOCKED - DEFINE %d ORDKLASSER!\n", player.ordklasse);
		printf("           .--._.--.\n");
		printf("          ( O     O )\n");
		printf("          /   . .   \\\n");
		printf("         .`._______.'.\n");
		printf("        /(           )\\\n");
		printf("      _/  \\  \\   /  /  \\_\n");
		printf("   .~   `  \\  \\ /  /  '   ~.\n");
		printf("  {    -.   \\  V  /   .-    }\n");
		printf("_ _`.    \\  |  |  |  /    .'_ _\n");
		printf(">_       _} |  |  | {_       _<\n");
		printf("         '-'|/   \\|`-`\n");
	}
		
	freopen(NULL, "w+", fp);
	fprintf(fp, "%d,%d,%d,%d", player.ordklasse, player.komma, player.test, player.ekstra);

	fclose(fp);
}