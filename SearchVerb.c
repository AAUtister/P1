#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
int main(void)
{

    // char *sentence[30] = {"Mit", "navn", "er", "Karl"};
    // // char filename[20];
    int i = 0, j = 0, ret = 0;  
    char *foundVerbs[i][j], ch, *x = {"<verb>"};
    FILE *filename;

    // sprintf(foundVerbs[90], "Verber.xml %s", sentence[30]);
    if ((filename = fopen("Verber.xml", "r")) == NULL)
    {
      perror("File open failure");
      exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(filename)) != EOF){
        printf("%c", ch);
        // ret = strcmp(ch, x);
        // if (ret == 1){
        //     foundVerbs 
        // }
    }

        // printf("%c", ch);
    // printf("Enter the verb u are looking for\n");
    // scanf("%s", &v);
	// for ()

    // // printf("The verb is: %s \n", v);

    fclose(filename);
    return 0;
}