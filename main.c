#include <stdio.h>
#include <string.h>


int main(void){
  char verbs [10][10] = {"er", "bliver", "går", "får", "synes","har","skal","vil","siger","kom" };

  char test_sentence [50] = "Jeg er glad, fordi jeg skal hjem"; 

  strstr(test_sentence, verbs);

  int yes = strcmp(test_sentence,verbs);


//yep cock
}