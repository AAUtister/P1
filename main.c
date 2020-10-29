#include <stdio.h>
#include <string.h>

int main(void)
{
  // char nothing[2] = " ";
  char nothing[1] = " ";
  char word[4];
  char verbs[4] = "er";
  char str1[50];
  char test_sentence[50] = "Jeg er glad, fordi jeg dum";
  char *token;
  int ret;
  // space = strtok(test_sentence, nothing);

  token = strtok(test_sentence, nothing);
  // int yes = strcmp(test_sentence, verbs);
  strcpy(str1, verbs);
  strcpy(word, token);

  while (token != NULL)
  {
    ret = strcmp(verbs, token);

    if (ret == 0)
    {
      printf("komma \n");
      printf("Token = %s og str1 = %s \n", token, str1);
      token = strtok(NULL, nothing);
    }
    else
    {

      token = strtok(NULL, nothing);
    }
  }

  // int YEP_COCK;
}
