/**
*       Parser module for the DCC Tokenizer
*
*/

#include <stdio.h>
#include <stdlib.h>

void release_result(char** result)
{
    if (result == NULL) return;

    if (result[1] != NULL) free(result[1]);
    if (result[2] != NULL) free(result[2]);

    free(result);

    return;
}

void write_xml(char** result, FILE* xml)
{
    char opentag[200], closetag[200], final[500];

    sprintf(opentag, "<%s>", result[1]);
    sprintf(closetag, "</%s>", result[1]);
    sprintf(final, "%s%s%s", opentag, result[2], closetag);

    fprintf(xml, "%s\n", final);

    release_result(result);

    return;
}
