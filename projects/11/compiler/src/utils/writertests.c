/**
*
*
*       Generic test functions for the code writer
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <utils/tests.h>


unsigned int writer_compare(char* path, unsigned int (*tested) (void), unsigned int size)
{

    char input[200], output[200], compare[200], buffer[2000];
    FILE *source, *vm;

    for (int i = 0; i < size; i++)
    {
        set_filenames(path, input, output, compare, i);

        source = fopen(input, "r");
        vm = fopen(output, "w");


        fclose(source);
        fclose(vm);
    }



}
