#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <table.h>

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
