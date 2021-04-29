/*
*   Parser for the Davi Compiler Collection (DCC)
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
int parse_line(char* buff, char** destination)
{
    // Indexes for the buffer and file
    int i, j, ind;

    ind = 0;
    for (i = 0, j = 0; buff[i] != '\0'; i++, j++)
    {
        switch (buff[i]) {
            case '/':
            {
                (*destination)[0] = '\0';
                return ind;
            }
            case ' ':
            case '\t':
            case '\r':
            case '\n':
            {
                (*destination)[j] = '\0';
                destination++;
                i++;
                ind++;
                j = 0;
                if (buff[i] == '\n' || ind == 3) return ind;
            }
        }
        if (buff[i] == '\0') return ind;

        (*destination)[j] = buff[i];

    }

}
