#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
        int num =0;
        char word[2000];
        char string[50];
        char test[100] = {0};

        while(test[0]!= '0')
        {
                FILE *in_file = fopen("test.rtf", "r");
                if (in_file == NULL)
                {
                        printf("Fil mangler\n");
                        exit(-1);
                }

                printf("Indsæt et ord (0 slutter)\n");
                scanf("%s", test);
                while ( fscanf(in_file,"%s", string) == 1)
                {
                        //Nyt for loop strstr(string, test) hvis ikke NULL. 
                        if(strstr(string, test)!=0) { //Hvis match er fundet.
                                num++;
                        }
                }
                printf("Ordet %s, blev fundet %d gange i teksten\n",test,num );
                num = 0;
                fclose(in_file);
        }
        return 0;
}