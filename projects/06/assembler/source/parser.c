#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <table.h>
#include <utils.h>

char* filename(char* str, int len)
{
    int i;
    char* ret;

    ret = malloc(len * sizeof(char));

    for (i = 0; str[i] != '.'; i++)
    {
        ret[i] = str[i];
    }

    strcat(ret, ".hack");

    return (ret);
}

unsigned int is_valid(char c)
{
    switch (c) {
        case '\n':
        case '/':
        case ' ':
        case '(':
        {
            return 0;
        }
    }

    return 1;
}


void add_ins(TABLE* root, char* cmd, FILE* stream)
{
    char* ptr, *val;
    if (strlen(cmd) < 1)
    {
        return;
    }

    if (strchr(cmd, '@') != NULL)
    {
        ptr = strchr(cmd, '@');
        val = to_bin(atoi(ptr+1));
        fprintf(stream, "%s\n", val);
    }
    else if (strlen(cmd) > 1)
    {
        char *dest, *comp, *jmp;
        int i, j, k;

        i = 0;
        j = 0;
        k = 0;

        dest = malloc(16*sizeof(char));
        comp = malloc(16*sizeof(char));
        jmp = malloc(16*sizeof(char));

        if (strchr(cmd, '=') != NULL)
        {
            for (; cmd[i] != '=' && cmd[i] != '\0'; i++) {
                dest[i] = cmd[i];
            }
            dest[i] = '=';
            dest[i+1] = '\0';
            fprintf(stderr, "Dest is now %s...\n", dest);
            dest = search_ins(root, dest);
            fprintf(stderr, "Found %s as value for dest...\n", dest);
            i++;

        }
        else
        {
            dest = "000";
        }

        for (; cmd[i] != ';' && cmd[i] != '\0' && cmd[i] != '\n'; j++, i++) {
            comp[j] = cmd[i];
        }

        comp[j] = '\0';
        fprintf(stderr, "Comp is now %s...\n", comp);
        comp = search_ins(root, comp);
        fprintf(stderr, "Found comp as being %s...\n", comp);

        if (comp == NULL)
        {
            fprintf(stderr, "comp is NULL\n");
            comp = "0000000";
        }

        i++;
        if (strchr(cmd, ';') != NULL)
        {

            for (; cmd[i] != '\0'; k++, i++) {
                jmp[k] = cmd[i];
            }
            jmp[k] = '\0';
            fprintf(stderr, "Jump is now %s\n", jmp);

            jmp = search_ins(root, jmp);
            fprintf(stderr, "Found value %s...\n", jmp);
            if (jmp == NULL)
            {
                fprintf(stderr, "jmp is NULL...\n");
                jmp = "000";

            }
        }
        else
        {
            jmp = "000";
        }

        fprintf(stream, "111");
        fprintf(stream, "%s", comp);
        fprintf(stream, "%s", dest);
        fprintf(stream, "%s", jmp);
        fprintf(stream, "\n");
    }
}

void parse(TABLE* root, FILE* f, FILE* dest)
{
    char buff[1000], cmd[1000];
    int i, index;

    // Check for errors in files and root
    if (f == NULL)
    {
        fprintf(stderr, "Source file provided does not exist\n");
        return;
    }
    else if (dest == NULL)
    {
        fprintf(stderr, "Destination provided does not exist.\n");
        return;
    }
    else if (root == NULL)
    {
        fprintf(stderr, "Table root is null");
        return;
    }

    fprintf(stderr, "About to read files\n");

    index = 1;
    while (fgets(buff, 1000, f) != NULL)
    {
        fprintf(stderr, "-- %i\n", index);
        index++;
        i = 0;
        while (is_valid(buff[i]))
        {
            cmd[i] = buff[i];
            i++;
        }
        cmd[i] = '\0';
        fprintf(stderr, "cmd is now %s...\n", cmd);
        add_ins(root, cmd, dest);
    }
}
