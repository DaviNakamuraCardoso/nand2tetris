/**
*       Analyzer module for the Davi Compile Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <tokenizer/reader.h>
#include <tokenizer/tokens.h>
#include <tokenizer/cleaner.h>
#include <tokenizer/parser.h>
#include <tokenizer/precomp.h>
#include <compengine/parser.h>
#include <compengine/compile.h>
#include <compengine/structure.h>


/**
*
*   Private functions
*
*/
static void get_tokens(char* tokens);
static char* get_name(char* filename);
static unsigned int is_file(char* path);
static unsigned int is_source(char* path);
static void analyze_file(char* file);
static void analyze_directory(char* directory);
static void cleanup(void);


void compile(char* filename)
{
    char* tokens, *content, *name;
    int i = 0;
    FILE* object, *target;

    target = fopen(get_name(filename), "w");

    tokens = tokenize(filename);
    get_tokens(tokens);

    object = fopen("object.xml", "r");

    CODE c = {.source=object, .target=target, .identation=&i};

    compile_class(&c);

    fclose(object);
    fclose(target);
    return;

}

void analyze(char* path)
{
    if (is_source(path)) analyze_file(path);
    else analyze_directory(path);

    cleanup();

    return;
}


static void analyze_file(char* file)
{
    if (is_source(file)) compile(file);
    return;
}

static void analyze_directory(char* directory)
{
    DIR* dir;
    char path[400];
    struct dirent* de;

    dir = opendir(directory);

    while ((de = readdir(dir)) != NULL)
    {
        sprintf(path, "%s/%s", directory, de->d_name);
        analyze_file(path);
    }

    closedir(dir);

    return;

}


static void get_tokens(char* tokens)
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

static char* get_name(char* filename)
{
    char* name, *end;

    name = malloc(strlen(filename) * sizeof(char));
    strcpy(name, filename);

    end = strstr(name, ".jack");

    end[1] = 'x';
    end[2] = 'm';
    end[3] = 'l';
    end[4] = '\0';

    return name;

}

static unsigned int is_source(char* path)
{
    return (strstr(path, ".jack") != NULL);
}

static void cleanup(void)
{
    remove("tokens.out");
    remove("object.xml");
    remove("tokens.xml");
}
