#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
int main(void)
{

    // // char filename[20];
    int j = 0, line_num = 1, find_result = 0, i = 0;
    char ch, str[512], temp[512], *verbarr[50], *(*ptr)[50] = &verbarr;

    FILE *filename;

    // sprintf(foundVerbs[90], "Verber.xml %s", sentence[30]);
    if ((filename = fopen("Verber.txt", "r")) == NULL)
    {
        perror("File open failure");
        exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(filename)) != EOF)
    {
        while (fgets(temp, 512, filename) != NULL)
        {
            if ((strstr(temp, str)) != NULL)
            {
                printf("A match found on line: %d\n", line_num);
                printf("%s\n", temp);
                (*ptr)[j] = temp;
                printf("String %d : %s\n", j + 1, (*ptr)[j]);
                j++;
                line_num++;
                find_result++;
            }
        }
    }

    for (j = 0; j < 5; j++)
    {
        printf("String %d : %s\n", j + 1, (*ptr)[j]);
    }
    fclose(filename);
    return 0;
}