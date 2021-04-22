#include <stdio.h>
#include <stdlib.h>

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
