#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ord.h"


int xmlreader()
{
    word o[50]; //plads til 50 ord structs
    //char* s = "Hej";
    strcpy(o[0].ord, "hej");
    printf("ORD : %s\n",o[0].ord);
    o[0].klasse = SUB;
    printf("KLASSE : %d\n", o[0].klasse); // skal printe 0 fordi verb er det foerste i enum
    FILE *fp;

    fp = fopen("RO12.xml", "r");

    mxml_node_t *tree;

    tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);

    fclose(fp);
    int i = 0;
    mxml_node_t *node;

    for (node = mxmlFindElement(tree, tree, "opslagsord", NULL,
                                NULL, MXML_DESCEND);
         node != NULL;
         node = mxmlFindElement(node, tree, "opslagsord", NULL,
                                NULL, MXML_DESCEND))
    {
        const char *tekst = mxmlGetText(node,0);
        if (!(strcmp(tekst,"penis"))){
            printf("\n%s %d", tekst, i);
        }
        i++;
        
        
    }
}

char ** ReadTextFromFile() {
    FILE *fp;
   int lenght;

   fp = fopen("tekst1.txt", "r");

   fseek(fp, 0, SEEK_END);

   lenght = ftell(fp);

   fclose(fp);

   printf("Total size of file.txt = %d bytes\n", lenght);
    
    
    FILE *file_p = fopen("tekst1.txt", "r");
    int i = 0;
    word w[lenght]; // lenght virker ikke ordenligt
    const char s[4] = " \n";
    char *token;
    char ** tekst_array = calloc(199, sizeof(char*)); // Giver segfault med malloc fordi den ikke garantere at heapen er null ifoelge Anders


    if (file_p == NULL) {
            printf("Fejl. Filen kunne ikke findes.\n");
            exit(EXIT_FAILURE);
    }
    
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("txt before loops \n");
    while ((read = getline(&line, &len, file_p)) != -1) {
        strcat(tekst, line);
    }


    fclose(file_p);
    
    token = strtok(tekst, s);


    while(token != NULL) {
        tekst_array[i++] = token;
        token = strtok(NULL, s);
        
    };
    printf("end of txt \n");
    return tekst_array;
}














char ** ReadVerbFromFile() {
    FILE *file_p = fopen("verbs_ascii_friendly.txt", "r");
    int i = 0;
    char file_content[600000];
    const char s[3] = "\n";
    char *token;
    char ** verb_array = malloc(442292 * sizeof(char*));

    if (file_p == NULL) {
            printf("Fejl. Filen kunne ikke findes.\n");
            exit(EXIT_FAILURE);
    }
   
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    printf("verb before loops \n");
    while ((read = getline(&line, &len, file_p)) != -1) {
        strcat(file_content, line);
    }

    fclose(file_p);
    
    token = strtok(file_content, s);

    while(token != NULL) {
        verb_array[i++] = token;
        token = strtok(NULL, s);
    };
    printf("end of verb \n");
    return verb_array;
}
