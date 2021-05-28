/**
*       Analyzer module for the Davi Compile Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer/reader.h>
#include <tokenizer/tokens.h>
#include <tokenizer/cleaner.h>
#include <tokenizer/parser.h>
#include <tokenizer/precomp.h>
#include <compengine/parser.h>
#include <compengine/compile.h>
#include <compengine/structure.h>

void get_tokens(char* tokens);

void compile(char* filename)
{
    char* tokens, *content;
    int i = 0;
    FILE* object, *target;

    target = fopen("file.xml", "w");

    tokens = tokenize(filename);
    get_tokens(tokens);

    object = fopen("object.xml", "r");

    CODE c = {.source=object, .target=target, .identation=&i};

    compile_class(&c);

    fclose(object);
    fclose(target);
    return;

}

void get_tokens(char* tokens)
{
    char* start, *end, *current;
    FILE* f = fopen("object.xml", "w");

    start = strchr(tokens, '>')+2;
    end = strrchr(tokens, '<');


    for (current = start; current < end; current++)
    {
        if (*current == '\t') continue;
        fputc(*current, f);
    }

    fclose(f);

    return;
}
