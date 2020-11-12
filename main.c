#include "txt-read.h"
#include "verb-read.h"
#include <ctype.h>
// Mighty shit

int main() {
	int x = 0;
	char ** verb_array = diller();
	char ** tekst_array = diller_1();

	int c = 0;
	while (tekst_array[c] != '\0') {
		c++;
	}

	int binary_shit[c];

    while (x <= c-1){
		for (int i = 0; i <= 44233; i++){
        
		  if (strcmp(tekst_array[x], verb_array[i])){
		  	binary_shit[x] = 0;
		  }
		  else{
			printf("\nFundet paa , %d plads, ordet er %s", i, tekst_array[x]);
			binary_shit[x] = 1;
			x++;
		  }
		}
	x++;
	}
	FILE *output;
	output = fopen("output.txt", "w");

	int looperboi = 0;
	while (looperboi < c) { // For hvert ord
		int p = 0;
		if (binary_shit[looperboi] == 1) { // Check om det er verbum
			while (tekst_array[looperboi][p] != '\0') {
				fprintf(output, "%c", toupper(tekst_array[looperboi][p]));
				p++;	
			
			}fprintf(output, " ");
			} else {
			while (tekst_array[looperboi][p] != '\0') {
				fprintf(output, "%c", tekst_array[looperboi][p]);
				p++;	
			}}
			fprintf(output, " ");
		looperboi++;
	}
	fclose(output);
return 0;
}