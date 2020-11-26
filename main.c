#include "reader.h"
<<<<<<< HEAD
#include "rules.h"
=======
// #include "rules.h"
#include "nexus.h"
>>>>>>> 3143de5f4d679d67b2fca39b52064237818b7043
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int x = 0;
	char **verb_array = ReadVerbFromFile();	
	char **tekst_array = ReadTextFromFile();
<<<<<<< HEAD
	char *found_rule[100000];
=======
	// char **found_rule = rules(*tekst_array);
	// printf("\n %s", found_rule[0]);
	char nexus(char **tekst_array,char **verb_array);
>>>>>>> 3143de5f4d679d67b2fca39b52064237818b7043
	int c = 0;
	while (tekst_array[c] != NULL)
	{
		*found_rule[c] = **rules(tekst_array[c]);
		printf("%s and %s\n ", found_rule[c], tekst_array[c]);
		c++;
	}
	// HEj
	int binary_shit[c];

	while (x <= c - 1)
	{
		for (int i = 0; i <= 44233; i++)
		{

			if (strcmp(tekst_array[x], verb_array[i]))
			{
				binary_shit[x] = 0;
			}
			else
			{
				printf("\nFundet paa , %d plads, ordet er %s", i, tekst_array[x]);
				binary_shit[x] = 1;
				x++;
			}
		}
		x++;
	}
	FILE *output;
	output = fopen("output.txt", "w");

	int iterator = 0;
	while (iterator < c)
	{ // For hvert ord
		int p = 0;
		if (binary_shit[iterator] == 1)
		{ // Check om det er verbum
			while (tekst_array[iterator][p] != '\0')
			{
				fprintf(output, "%c", toupper(tekst_array[iterator][p]));
				p++;
			}
			fprintf(output, " ");
		}
		else
		{
			while (tekst_array[iterator][p] != '\0')
			{
				fprintf(output, "%c", tekst_array[iterator][p]);
				p++;
			}
		}
		fprintf(output, " ");
		iterator++;
	}
	fclose(output);
	free(tekst_array);
	free(verb_array);
	return 0;
}
