#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **rules(char *tekst_array[])
{
    char *hv_array[14] = {"hvem", "hvad", "hvornaar", "hvordan", "hvor", "hvilken", "hvorfra", "hvorhen", "hvilket", "hvilke"};
    int c = 0, x = 0;

    // while (tekst_array != '\0')
    // {
    //     printf("%s \n", tekst_array[c]);
    //     c++;
    // }
    while (tekst_array[c] != NULL)
    {

        if (*tekst_array[c] != '\0')
        {
            printf("%s \n", tekst_array[c]);
        }
        c++;
    }

    int found_rule[c];
    for (int j = 0; j < 10; j++)
    {

        for (int i = 0; i <= c; i++)
        {

            int ret = strcmp(tekst_array[i], hv_array[j]);

            if (ret == 0)
            {
                printf("YES ---i = %d and x = %d \n tekst = %s og hv = %s \n", i, j, tekst_array[i], hv_array[j]);
                found_rule[j] = 0;
            }
            else
            {
                printf("NOPE -------------------i = %d and x = %d \n tekst = %s og hv = %s \n", i, j, tekst_array[i], hv_array[j]);
                // printf("nope .---------. i = %d\n ", i);
                found_rule[j] = 1;
            }
        }
        printf("LOOP == %d \n \n", j);
    }

    return found_rule;
}