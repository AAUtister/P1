#include "reader.h"
#include "rules.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mighty shit
// ToDo: Tilfoej flere ordklasser at sortere efter
enum
{
	VERB = 1,
};

int main()
{
	int x = 0;
	char **verb_array = read_from_file("verbs_ascii_friendly.txt", 442292, "\n");
	char **tekst_array = read_from_file("tekst1.txt", 199, " \n");
	int c = 0;
	while (tekst_array[c] != NULL)
	{
		c++;
	}
	char **found_rule = rules(*tekst_array);
	printf("\n %s", found_rule[0]);
	int word_class[c];

	while (x <= c - 1)
	{
		for (int i = 0; i <= 44233; i++)
		{

			if (strcmp(tekst_array[x], verb_array[i]))
			{
				word_class[x] = 0;
			}
			else
			{
				printf("\nFundet paa , %d plads, ordet er %s", i, tekst_array[x]);
				word_class[x] = 1;
				x++;
			}
		}
		x++;
	}
	FILE *output;
	output = fopen("output.txt", "w");

	int itr = 0;
	while (itr < c)
	{ // For hvert ord
		int p = 0;
		if (word_class[itr] == VERB)
		{
			while (tekst_array[itr][p] != '\0')
			{
				fprintf(output, "%c", toupper(tekst_array[itr][p]));
				p++;
			}
			fprintf(output, " ");
		}
		else
		{
			while (tekst_array[itr][p] != '\0')
			{
				fprintf(output, "%c", tekst_array[itr][p]);
				p++;
			}
		}
		fprintf(output, " ");
		itr++;
	}
	fclose(output);
	free(tekst_array);
	free(verb_array);
	return 0;
}