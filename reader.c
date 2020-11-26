#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** read_from_file(char* _FILENAME_, int bytesize, char* delim){
    FILE *fp;
    int length = 0,
        i = 0;

    /* Get bytesize of file */
    fp = fopen(_FILENAME_, "r");
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fclose(fp);
    printf("Total size of %s = %d bytes\n", _FILENAME_, length);

    FILE *file_p = fopen(_FILENAME_, "r");
    if (file_p == NULL){
        printf("Fejl. Filen kunne ikke findes.\n");
        exit(EXIT_FAILURE);
    }

    // length virker ikke ordenligt
    char file_content[600000];
    char *token;
    char ** charArr = calloc(bytesize, sizeof(char*));

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file_p)) != -1) {
        strcat(file_content, line);
    }

    fclose(file_p);

    /* Split file content into array of words */
    token = strtok(file_content, delim);
    while(token != NULL) {
        char *tok = calloc(sizeof(token), sizeof(char));

        strcpy(tok, token);
        charArr[i++] = tok;
        token = strtok(NULL, delim);
    };

    return charArr;
}
