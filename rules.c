#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** rules(char **tekst_array)
{
    char *hv_array[10][14] = {"hvem", "hvad", "hvornaar", "hvordan", "hvor", "hvilken", "hvorfra", "hvorhen", "hvilket", "hvilke"};
    int c = 0, x = 0;

    while (tekst_array[c] != NULL)
    {
        c++;
    }

    char found_rule[c];
    while (x <= c - 1)
    {

        for (int i = 0; i <= c; i++)
        {

            if (strcmp(tekst_array[x], *hv_array[i]))
            {
                found_rule[x] = 0;

            }
            else
            {
                printf("\nFundet paa , %d plads, ordet er %s", i, tekst_array[x]);
                found_rule[x] = 1;
                x++;
            }
        }
        x++;
    }
    return *found_rule;
}