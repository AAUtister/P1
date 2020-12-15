#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utf8.h"


int str_cmp(const char *str1, const char *str2);
void rules(char *tekst_array[], int found_rule[])
{
    int x = 11;
    char *hv_array[11] = {"hvem", "hvad", "hvornår", "hvorfor", "hvordan", "hvor", "hvilken", "hvorfra", "hvorhen", "hvilket", "hvilke"};
    int c = 0;

    while (tekst_array[c] != NULL)
    {
        c++;
    }

    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < x; j++)
        {
            int ret = str_cmp(tekst_array[i], hv_array[j]);
            if (ret == 0)
            {
                found_rule[i] = ret;
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
