#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

void achievements() {
	typedef struct {
		int score;
	} profile;


	FILE *fp = fopen("savegame.csv", "r");
	
	if (fp == NULL){
        printf("Savegame kunne ikke findes. Opretter savegame...\n");
        fp = fopen("savegame.csv", "w+");
        fprintf(fp, "%d", 0);
        fclose(fp);
        fp = fopen("savegame.csv", "r");
        printf("Savegame oprettet!\n");
    }

    profile player;

    fscanf(fp, "%d", &player.score);
	
	player.score = player.score + 1;
	if (player.score == 50) {
		printf("ACHIEVEMENT UNLOCKED - DEFINE %d ORDKLASSER!\n", player.score);
	}
    // printf("%d\n", player.score);
	
	
	freopen(NULL, "w+", fp);
	fprintf(fp, "%d", player.score);

	fclose(fp);
}