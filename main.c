#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    FILE *file_p = fopen("/Users/frederikfrohn/Desktop/10nov/verb_v1.txt", "r");
    int i = 0;
    int x = 0;
    char tekst[600000];
    const char s[3] = "\n";
    char *token;
    char *tekst_array[60000];

    if (file_p == NULL) {
            printf("Fejl. Filen kunne ikke findes.\n");
            exit(EXIT_FAILURE);
    }
   
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    strcpy(tekst, "_VERBS_\n");

    while ((read = getline(&line, &len, file_p)) != -1) {
        strcat(tekst, line);
    }

    fclose(file_p);
    
    token = strtok(tekst, s);


    while(token != NULL) {
        tekst_array[i++] = token;
        token = strtok(NULL, s);
    };
    
    // printf("NY NY NY NY NY NY %d", i);

    // Printer array
    for (x = 0; x < i; x++){
        printf("\n%s", tekst_array[x]);
    }

    printf("\n%s", tekst_array[0]);

    // printf("\n%s",tekst_array[31]); //Eksempel
    
    return 0;
}


int func2 () {
   char str1[15];
   char str2[15];
   int ret;

   strcpy(str1, "Å");
   strcpy(str2, "Æ");

   ret = strcmp(str1, str2);

   printf("%d", ret);
   
   if(ret < 0) {
      printf("str1 is less than str2");
   } else if(ret > 0) {
      printf("str2 is less than str1");
   } else {
      printf("str1 is equal to str2");
   }
   
   return(0);
}