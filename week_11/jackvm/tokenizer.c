#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"
#include "tokens.h"
 
#define LINESIZE 300
#define CMDSIZE 30


unsigned int isnewline(char c)
{
    return (c == '\n') || (c == '\r'); 
}

char* readline(FILE* stream, char* buff)
{
    int i = 0; 
    char c;
    while ((c = fgetc(stream)) != EOF)
    {
        if (isnewline(c)) 
        {
            buff[i] = '\0'; 
            return buff; 
        }
        buff[i++] = c;
    }
    buff[i] = '\0'; 

    return NULL; 
}


char** parseline(char* line, char** contents)
{

    int i = 0, k = 0;

    for (; i < 3 && line[k] != '\0'; i++) 
    {
        int j;
        for (j = 0; !isblank(line[k]) && line[k] != '\0'; j++, k++)
        {
           contents[i][j] = line[k]; 
        }

        contents[i][j] = '\0';

        for (; isblank(line[k]) && line[k] != '\0'; k++);
    }

    for (int l = i; l < 3; l++)
        contents[l][0] = '\0'; 

    return contents; 
} 

void* tokenize(FILE* stream)
{
    char line[LINESIZE]; 
    char** cmds = calloc(sizeof(char*), 3); 
    for (int i = 0; i < 3; i++) cmds[i] = calloc(sizeof(char), CMDSIZE);

    while (readline(stream, line) != NULL)
    {
        parseline(line, cmds); 
    }

    parseline(line, cmds); 

    return NULL; 
}


