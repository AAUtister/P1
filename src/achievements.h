typedef struct {
		int ordklasse;
		int komma;
		int help;
		int ekstra;
		char navn[20];

} profile;

typedef enum {
	ORDKLASSE,
	KOMMA,
	HELP,
	EKSTRA
} scoretypes;

void achievements(int point, int scoretype);
int getScores(int scoretype);