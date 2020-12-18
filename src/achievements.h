#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H
typedef struct {
		int ordklasse;
		int komma;
		int help;
		int ekstra;
		char navn[20];

} profile;

void achievements(int point, int scoretype);
int getScores(int scoretype);
#endif
