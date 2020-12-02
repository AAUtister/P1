#include "mxml.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <locale.h>
//#include <wchar.h>



int main()
{
    //setlocale(LC_ALL,"");

    FILE *fp;

    fp = fopen("RO12.xml", "r");

    ;
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
    /*     do{
        node = mxmlFindElement(tree, tree, "opslagsord", NULL, NULL, MXML_DESCEND);
        
        const char *tekst = mxmlGetText(node,0);

        printf("\n%s %d",tekst,i);
        i++;

    }while(node != NULL);
        
 */
}