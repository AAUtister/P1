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
    const char s[3] = ".";
    char *token;
    int length = 0, i = 0;  
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fclose(fp);

    FILE *file_p = fopen(_FILENAME_, "r");

    char *file_content = calloc(length, sizeof(char));
    char **charArr = calloc(length, sizeof(char *));
    printf("Total size of txt = %d bytes\n", length);
    char *buffer;
    size_t len = length;
    ssize_t read;

    buffer = (char *)malloc(len * sizeof(char));

    if (buffer == NULL)
    {
        printf("No space to allocate");
        return 0;
    }

    while ((read = getline(&buffer, &len, file_p)) != -1)
    {
        strcat(file_content, buffer);
    }

    fclose(file_p);
    token = strtok(file_content, s);

    while (token != NULL)
    {
        char *tok = (char *)calloc(sizeof(token), sizeof(char) + 1000);
        strcpy(tok, token);
        charArr[i] = tok;
        token = strtok(NULL, s);
        i++;
        int j = 0, k = 0;
        if (tok[0] == ' ')
        {
            char *newtok = (char *)calloc(sizeof(token), sizeof(char) + 1000);
            for (j = 0, k = 1; tok[k] != '\0'; j++, k++)
            {
                newtok[j] = tok[k];
            }
            strcpy(tok, newtok); // toktok
            j = 0, k = 0;
        }
    };
    free(buffer);
    free(file_content);

    return charArr;
}