#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** read_from_file(char* _FILENAME_, int *plength, char* delim){
    FILE *fp;
    int length = 0,
        i = 0;

    /* Get bytesize of file */
    fp = fopen(_FILENAME_, "r");
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fclose(fp);
    printf("Total size of %s = %d bytes\n", _FILENAME_, length);

    *plength = length;

    FILE *file_p = fopen(_FILENAME_, "r");
    
    if (file_p == NULL){
        printf("Fejl. Filen kunne ikke findes.\n");
        exit(EXIT_FAILURE);
    }

    char *  file_content = calloc(length, sizeof(char) + 1000);
    char *  token;
    char ** charArr = calloc(length, sizeof(char*) + 1000);

    char *  buffer;
    size_t  len = length;
    ssize_t read;

    buffer = (char*)malloc(len *sizeof(char) + 1000);
    
    if(buffer == NULL){
        printf("No space to allocate");
        return 0;
    }

    while ((read = getline(&buffer, &len, file_p)) != -1) {
        strcat(file_content, buffer);
    }

    fclose(file_p);

    /* Split file content into array of words */
    token = strtok(file_content, delim);

    while(token != NULL) {
        char *tok = (char *) calloc(sizeof(token), sizeof(char) + 1000);
        strcpy(tok, token);
        charArr[i] = tok;
        token = strtok(NULL, delim);
        i++;
    };
    
    free(buffer);
    free(file_content);

    return charArr;
}
