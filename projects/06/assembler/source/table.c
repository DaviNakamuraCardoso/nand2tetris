#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>
#include <table.h>


TABLE* init_table(TABLE* root, char c)
{
    TABLE* new;
    int i, a;

    new = malloc(sizeof(TABLE));
    a = (int) c;

    for (i = 0; i < 200; i++) {
        new->next[i] = NULL;
    }
    new->value = NULL;
    new->locked = 0;

    if (root != NULL) {
        root->next[a] = new;
    }

    return new;
}


void add_command(TABLE* root, char* cmd, char* value)
{
    TABLE* current, *new;
    int i, a;

    current = root;

    for (i = 0; cmd[i] != '\0'; i++) {
       a = (int) cmd[i];
       new = current->next[a];
       if (new == NULL) {
            new = init_table(current, a);
       }
       current = new;

    }

    current->value = strdup(value);

    return;

}

void add_values(TABLE* root, FILE* f)
{
    char cmd[200], val[200], buff[400];
    int i, j;

    if (f == NULL) {
        printf("File pointer is NULL\n");
        return;
    }
    while (fgets(buff, 400, f) != NULL) {

        for (i = 0; buff[i] != ','; i++) {
            cmd[i] = buff[i];
        }
        cmd[i] = '\0';
        i++;

        for (j = 0; buff[i] != '\0'; j++, i++) {
            val[j] = buff[i];
        }
        val[j-1] = '\0';
        fprintf(stderr, "Adding command %s with %s as value\n", cmd, val);

        add_command(root, cmd, val);
    }


     return;
}

char* search_ins(TABLE* root, char* cmd)
{
    int i, a;
    TABLE* current;
    char* ptr;

    current = root;
    ptr = NULL;
    for (i = 0; cmd[i] != '\0' && current != NULL; i++) {
        a = cmd[i];
        current = current->next[a];
    }
    if (current != NULL)
    {
        ptr =  current->value;
    }

    return ptr;
}

unsigned int is_numeric(char* buff)
{
    int i;
    for (i = 0; buff[i] != '\0'; i++)
    {
        if ((buff[i]) < 48 || (buff[i] > 57))
        {
            return 0;
        }
    }
    return 1;
}

void check_line(TABLE* root, char* cmd, int* memindex, FILE* out)
{
    char *ptr, buff[200], *existing, *new;
    int i, l, val;
    // Do nothing for invalid lines

    l = strlen(cmd);
    if (l <= 1)
    {
        return;
    }


    fprintf(stderr, "Checking %s...\n", cmd);


    // Check for a variable
    if (strchr(cmd, '@') != NULL)
    {
        ptr = strchr(cmd, '@');
        for (i = 1; ptr[i] != '\0' && ptr[i] != '\n'; i++)
        {
            buff[i-1] = ptr[i];
        }
        buff[i-2] = '\0';

        fprintf(stderr, "Variable: %s\n", buff);
        existing = search_ins(root, buff);

        if (is_numeric(buff))
        {
            fprintf(stderr, "Found numeric variable: %s..\n", buff); 
            fprintf(out, "@%s\n", buff);
        }
        else if (existing != NULL)
        {
            fprintf(stderr, "Variable already exists at the value of %s\n", existing);
            fprintf(out, "@%s\n", existing);
        }
        else
        {
            new = malloc(16*sizeof(char));
            val = *memindex;

            sprintf(new, "%i", val);
            fprintf(stderr, "Adding variable %s with value %i...\n", buff, val);
            add_command(root, buff, new);
            fprintf(out, "@%i\n", val);
            (*memindex)++;
        }
    }

    else if (strchr(cmd, '(') == NULL)
    {
        fprintf(out, "%s\n", cmd);
    }


    return;

}

unsigned int valid_char(char c)
{
    switch (c) {
        case '\n':
        case '/':
        case 0:
        {
            return 0;
        }
    }

    return 1;
}

void setup_vars(TABLE* root, FILE* f)
{
    int i, j, memindex;
    char buff[1000], cmd[1000];
    FILE *out;

    memindex = 16;

    out = fopen("hack.out", "w");
    while (fgets(buff, 1000, f) != NULL)
    {
        i = 0;
        j = 0;
        while (valid_char(buff[i]))
        {
            if (buff[i] == ' ')
            {
                i++;
                continue;
            }
            cmd[j] = buff[i];
            i++;
            j++;
        }
        cmd[j] = '\0';
        fprintf(stderr, "Checking line %s...\n", cmd);
        check_line(root, cmd, &memindex, out);
    }
    fclose(out);

    return;
}


void find_label(TABLE* root, char* cmd, int* line_num)
{
    int i, j, length;
    char *ptr, buff[400], *new;

    length = strlen(cmd);

    // Check for a LABEL
    if (strchr(cmd, '(') != NULL)
    {
        ptr = strchr(cmd, '(');
        for (i = 1; ptr[i] != ')'; i++)
        {
            buff[i-1] = ptr[i];
        }
        buff[i-1] = '\0';
        fprintf(stderr, "LABEL found: %s\n", buff);


        new = malloc(16*sizeof(char));
        sprintf(new, "%i", *line_num);
        add_command(root, buff, new);
        return;

    }
    else if (length > 1)
    {
        (*line_num)++;
    }

}

void setup_labels(TABLE* root, FILE* f)
{
    int i, j, line_num;
    char buff[1000], cmd[1000];

    line_num = 0;

    while (fgets(buff, 1000, f) != NULL)
    {
        i = 0;
        j = 0;
        while (valid_char(buff[i]))
        {
            if (buff[i] == ' ')
            {
                i++;
                continue;
            }
            cmd[j] = buff[i];
            i++;
            j++;
        }
        cmd[j] = '\0';
        fprintf(stderr, "Searching for labels in line %s...\n", cmd);
        find_label(root, cmd, &line_num);
    }

    return;

}
