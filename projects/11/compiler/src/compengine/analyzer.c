/**
*       Analyzer module for the Davi Compile Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <compengine/compile.h>
#include <tokenizer/reader.h>
#include <tokenizer/cleaner.h>
#include <tokenizer/parser.h>
#include <tokenizer/precomp.h>
#include <compengine/parser.h>
#include <compengine/structure.h>


/**
*
*   Private functions
*
*/
static void get_tokens(char* tokens);
static void get_name(char* filename, char* buffer);
static unsigned int is_file(char* path);
static unsigned int is_source(char* path);
static void analyze_file(char* file);
static void analyze_directory(char* directory);
static void cleanup(void);
static CODE* get_code(char* filename);


void compile(char* filename)
{
    CODE* c = get_code(filename);
    compile_class(c);
    release_code(c);

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

static void get_name(char* filename, char* buffer)
{
    int i;
    char *current;

    for (i = 0, current = filename; strcmp(current, ".jack") != 0; i++, current++)
    {
        buffer[i] = filename[i];
    }
    buffer[i] = '\0';

    strcat(buffer, ".xml");

    return;
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

CODE* get_code(char* filename)
{
    char* tokens, name[300];
    FILE* source, *target;
    CODE* c;

    get_name(filename, name);
    target = fopen(name, "w");

    tokens = tokenize(filename);
    get_tokens(tokens);

    source = fopen("object.xml", "r");

    c = new_code(source, target);

    free(tokens);

    return c;
}
