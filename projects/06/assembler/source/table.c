#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

        add_command(root, cmd, val);
    }

    fclose(f);

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

unsigned int is_valid(char c)
{
    switch (c) {
        case '\n':
        case '/':
        case ' ':
        {
            return 0;
        }
    }

    return 1;
}

char* to_bin(int dno)
{
    int rem, f, i;
    char* str;
    f = 0;
    str = malloc(16*sizeof(char));
    for (i = 0; i < 16; i++)
    {
        str[i] = (char) 48;
    }

    while(dno != 0)
    {
        rem = dno % 2;
        str[15-f] = (char) (rem+48);
        dno = dno / 2;
        f++;

    }

    return str;
}

void add_ins(TABLE* root, char* cmd)
{
        char* ptr, *val;

        if (strchr(cmd, '@') != NULL)
        {
            ptr = strchr(cmd, '@');
            val = to_bin(atoi(ptr+1));
            printf("%s\n", val);
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
                dest = search_ins(root, dest);
            }
            else
            {
                dest = "000";
            }
            i++;
            for (; cmd[i] != ';' && cmd[i] != '\0'; j++) {
                comp[j] = cmd[i];
                i++;
            }
            comp[j-1] = '\0';
            comp = search_ins(root, comp);

            if (strchr(cmd, ';') != NULL)
            {

                for (; cmd[i] != '\0'; k++, i++) {
                    jmp[k] = cmd[i];
                }
                jmp[k-1] = '\0';
                jmp = search_ins(root, jmp);
            }
            else
            {
                jmp = "000";
            }


            printf("111");
            printf("%s", comp);
            printf("%s", dest);
            printf("%s", jmp);
            printf("\n");
        }
}

void add_symbols(TABLE* root, FILE* f)
{
    char buff[400], cmd[400];
    int i;

    if (f == NULL)
    {
        printf("Destination provided does not exist\n");
        return;
    }

    while (fgets(buff, 400, f) != NULL)
    {
        i = 0;
        while (is_valid(buff[i]))
        {
            cmd[i] = buff[i];
            i++;
        }
        cmd[i] = '\0';
        add_ins(root, cmd);
    }
}
