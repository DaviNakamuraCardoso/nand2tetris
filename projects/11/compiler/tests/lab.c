#include <stdio.h>


void good_morning(void);


int main(void)
{
   good_morning();



}

void good_morning(void)
{
    unsigned int is_day;
    hello:
    {
        printf("Is it day? ");
        scanf("%i", &is_day);
        if (is_day) goto salute;
        goto end;


        salute:{
            puts("Good Morning");
            goto end;
        }
    }
    goto hello;

    end:{
        if (is_day) goto hello;
        goto goodnight;

    }

    goodnight:{
        puts("Good night");
        return;
    }
}
