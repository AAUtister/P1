#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int str_cmp(const char *str1, const char *str2);
void rules(char *tekst_array[], int found_rule[])
{
    char *hv_array[17] = {"hvem", "hvad", "hvornår", "hvorfor", "hvordan", "hvor", "hvilken", "hvorfra", "hvorhen", "hvilket", "hvilke", "fordi", "at", "end", "man", "for", "men"};
    int c = 0;

    while (tekst_array[c] != NULL)
    {
        c++;
    }
    printf("%d \n", c);

    int banan = sizeof(hv_array) / sizeof(int);
    printf("%i\n", banan);
    int x = 17;

    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < x; j++)
        {
            int ret = str_cmp(tekst_array[i], hv_array[j]);
            // printf("tekst = %s -- hv_array = %s \n", tekst_array[i], hv_array[j]);
            if (ret == 0)
            {
                // printf("\nYES ---i = %d and j = %d \n tekst = %s og hv = %s \n", i, j, tekst_array[i], hv_array[j]);
                found_rule[i] = ret;

                // printf("\n \n yes = %d \n \n", found_rule[i]);
                break;
            }
            else
            {
                found_rule[i] = ret;
            }
        }
    }
}

int str_cmp(const char *str1, const char *str2)
{   

    if (strlen(str1) != strlen(str2))
    {
        return 1;
    }
    for (int i = 0; i < strlen(str1); i++)
    {
        if (str1[0] < 96)
        {
            return 1;
        }
        
        if (str1[i] != str2[i])
        {
            return 1;
        }
        
    }
    return 0;
}
