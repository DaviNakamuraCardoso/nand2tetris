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
    int i, j, ind, words;

    ind = 0;
    words = 0;
    for (i = 0, j = 0; buff[i] != '\0'; i++, j++)
    {
        switch (buff[i]) {
            case '/':
            {
                (*destination)[0] = '\0';
                return words;
            }
            case '\t':
            case 0:
            case 32:
            case '\b':
            case '\r':
            case '\n':
            {
                (*destination)[j] = '\0';
                destination++;
                i++;
                ind++;
                if (j > 0) words++;
                j = 0;
                if (buff[i] == '\n' || ind == 3) return words;
            }
        }
        if (buff[i] == '\0') return words;

        if ((buff[i] >= '0' && buff[i] <= '9') || (buff[i] >= 'a' && buff[i] <= 'z')
            || (buff[i] >= 'A' && buff[i] <= 'Z') || (buff[i] == '_' || buff[i] ==
        '-'))
        {
            (*destination)[j] = buff[i];
        }
        else {
            (*destination)[j] = '\0';
            destination++;
            i++;
            ind++;
            if (j > 0) words++;
            j = 0;
            if (buff[i] == '\n' || ind == 3) return words;

        }

    }

}
