#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
int main(void)
{

    char *sentence[30] = {"Mit", "navn", "er", "Karl"};
    // char filename[20];
    int N;
    char *foundVerbs, v;
    FILE *filename;

    sprintf(sentence[30], "Verber.xml", N);
    if ((filename = fopen("Verber.xml", "r")) == NULL)
    {
      perror("File open failure");
      exit(EXIT_FAILURE);
    }
    // printf("Enter the verb u are looking for\n");
    // scanf("%s", &v);

    // printf("The verb is: %s \n", v);

    fclose(filename);
    return 0;
}