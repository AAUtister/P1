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
    fseek(fp, SEEK_SET, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *file_content = calloc(length, sizeof(char) + 1000);
    char **charArr = calloc(length, sizeof(char *) + 1000);
    printf("Total size of txt = %d bytes\n", length);
    char *buffer;
    size_t len = length;
    ssize_t read;

    buffer = (char *)malloc(len * sizeof(char) + 1000);

    if (buffer == NULL)
    {
        printf("No space to allocate");
        return 0;
    }

    while ((read = getline(&buffer, &len, fp)) != -1)
    {
        buffer[strcspn(buffer, "\n")] = 0;
        strcat(file_content, buffer);
    }

    fclose(fp);

    token = strtok(file_content, s);

    while (token != NULL) {
        int b = 0;
        
        while (token[b]) {
            b++;
        }
        
        char *tok = (char *)calloc(b, sizeof(char) * 4);
        
        strcpy(tok, token);
        

        
        int j = 0, k = 0;
        
        if (tok[0] == ' ' /*|| tok[0] == '\n'*/) {
            
            char *newtok = (char *)calloc(sizeof(token), sizeof(char) + 1000);
            
            for (j = 0, k = 1; tok[k] != '\0'; j++, k++) {
                newtok[j] = tok[k];
            }
            
            strcpy(tok, newtok); // toktok
            free(newtok);

            j = 0, k = 0;
        }
        charArr[i] = tok;
        printf("%s\n", charArr[i]);

        i++;
        token = strtok(NULL, s);
        free(tok);
    };


    free(buffer);
    free(file_content);

    return charArr;
}