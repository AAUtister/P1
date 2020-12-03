#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **sentence_splitter(char *_FILENAME_)
{

    FILE *fp = fopen(_FILENAME_, "r");
    if (fp == NULL)
    {
        printf("Fejl. Filen kunne ikke findes.\n");
        exit(EXIT_FAILURE);
    }
    const char s[2] = " \n";
    char *token;
    int length = 0, i = 0;
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    char *file_content = calloc(length, sizeof(char));
    char **charArr = calloc(length, sizeof(char *));
    
    char * buffer;
    size_t len = length;
    ssize_t read;

    buffer = (char*)malloc(len *sizeof(char));
    
    if(buffer == NULL){
        printf("No space to allocate");
        return 0;
    }

    while ((read = getline(&buffer, &len, fp)) != -1) {
        strcat(file_content, buffer);
    }

    token = strtok(file_content, s);

    while (token != NULL)
    {
        char *tok = (char *)calloc(sizeof(token), sizeof(char) + 5);
        strcpy(tok, token);
        charArr[i] = tok;
        token = strtok(NULL, s);
        i++;
    };
    free(file_content);

    return charArr;
}