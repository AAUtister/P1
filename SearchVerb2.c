#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main(void){
    int j = 0, line_num = 1, find_result = 0, i = 0, N = 20;
    char ch, str[512], temp[512], filename[30];
    char matchede_verber[512], verbsfromfile[N];
    FILE *myfile;

    sprintf(filename, "Verber.txt", N);
    // sprintf(foundVerbs[90], "Verber.xml %s", sentence[30]);
    if ((myfile = fopen(filename, "r")) == NULL)
    {
        perror("File open failure");
        exit(EXIT_FAILURE);
    }
    // This is our loop to add verbs from our file to an array.
    for (int k = 0; k < N; k++){
        
    fscanf(myfile, "%s", &verbsfromfile[k]);

    printf("%c\n",verbsfromfile[k]);
  }


    return 0;
}