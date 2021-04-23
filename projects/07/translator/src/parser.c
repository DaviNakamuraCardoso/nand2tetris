/*
* Parser for the Davi Compiler Collection
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parser.h>

// Parse the provided filename to a .asm extension
char* parse_filename(filename)
char* filename;
{
    // Indexes for the filename and buffer
    int i, j, len;
    char* buffer;

    len = strlen(filename) + 4;
    buffer = malloc(len * sizeof(char));

    // Copies the filename up until the dot (or the end)
    for (i = 0, j = 0; filename[i] != '\0' && filename[i] != '.'; i++, j++)
    {
        buffer[j] = filename[i];
    }

    // Concatenates the buffer and asm
    strcat(buffer, ".asm");

    return buffer;
}


// Parse a line from the source file to a string
void parse_line(FILE* f, char* destination)
{
    // Indexes for the buffer and file
    int i, j;

    return;
}
