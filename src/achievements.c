#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

void achievements(int point) {
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
	
	player.score = player.score + point;
	if (player.score > 0 && !(player.score % 50)) {
		printf("ACHIEVEMENT UNLOCKED - DEFINE %d ORDKLASSER!\n", player.score);
	}
		
	freopen(NULL, "w+", fp);
	fprintf(fp, "%d", player.score);

	fclose(fp);
}