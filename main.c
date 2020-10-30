#include <stdio.h>
#include <string.h>

int main(void)
{
  // char nothing[2] = " ";
  char nothing[1] = " ";
  char *verbs[3][10] = {{"er"}, {"bliver"}, {"siger"}};
  char str1[50];
  char test_sentence[50] = "Jeg er glad, fordi jeg siger og bliver dum";
  char *token;
  int ret;
  // space = strtok(test_sentence, nothing);

  token = strtok(test_sentence, nothing);
  // int yes = strcmp(test_sentence, verbs);

  while (token != NULL)
  {
    ret = strcmp(verbs, token);

    for (verbs[0]; 0 < 3; +1)
    {

      if (ret == 0)
      {
        printf("komma \n");
        printf("Token = %s og str1 = %s \n", token, str1);
        token = strtok(NULL, nothing);
      }
      else
      {
        printf("Token = %s \n", token);
        token = strtok(NULL, nothing);
      }
    }
  }
}
