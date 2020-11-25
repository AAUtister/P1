#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **rules(char text_array)
{
    char hv_array = {"hvem", "hvad", "hvornaar", "hvordan", "hvor", "hvilken", "hvorfra", "hvorhen", "hvilket", "hvilke"};
    int c = 0, x = 0;
    while (text_array[c] != NULL)
    {
        c++;
    }

    char found_rule[c];
	while (x <= c - 1)
	{
		
		for (int i = 0; i <= 44233; i++)
		{

			if (strcmp(tekst_array[x], verb_array[i]))
			{
				found[x] = 0;
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
    return hv_array;
}