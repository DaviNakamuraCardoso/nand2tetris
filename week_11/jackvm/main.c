#include <stdio.h>
#include "tokenizer.h"


int main(int argc, const char** argv)
{
    FILE* stream = stdin;

    if (argc >= 3)
    {
        fprintf(stderr, "Illegal number of command line arguments: %i.\n", argc); 
    }
    else if (argc == 2)
    {
        stream = fopen(argv[1], "r");
    }

    tokenize(stream); 

    return 0; 

}
