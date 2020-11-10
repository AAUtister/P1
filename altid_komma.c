#include <stdio.h>
#include <string.h>

int main(void){
    char komma_bindeord [3][6] = {"fordi","men","da",};

    char tekst_array [11][20] = {"Jeg", "fordi", "elsker", "mad","men","mere", "vand", "da", "det", "er","noedvendigt"};

    for (int i = 0; i <= 11; i++){

        if (strcmp(tekst_array[i], komma_bindeord[0])){
          printf("0");
        }
        else{
          printf("1");
        }
        
        
    }
    
    


}