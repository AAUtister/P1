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
	int length_verb = 0;
	int length_tekst = 0;
	int x = 0;
	char **tekst_array = read_from_file("tekst1.txt", &length_tekst, " \n");
	char **found_array = rules(tekst_array);
	char **verb_array = read_from_file("verbs_ascii_friendly.txt", &length_verb, "\n");
	int tekst_count = 0;
	while (tekst_array[tekst_count] != NULL)
	{
		printf("Found array = %s", found_array[tekst_count]);
		tekst_count++;
	}

	int verb_count = 0;
	while (verb_array[verb_count] != NULL)
	{
		verb_count++;
	}

	int word_class[tekst_count];

	while (x < tekst_count)
	{
		for (int i = 0; i < verb_count; i++)
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
	while (itr < tekst_count)
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
