/**
*
*
*       Generic test functions for the code writer
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <compengine/compile.h>
#include <tokenizer/reader.h>
#include <utils/tests.h>


unsigned int writer_compare(char* path, unsigned int (*tested) (CODE*), unsigned int size)
{

    char input[200], output[200], compare[200], buffer[2000], *result, *expected;
    FILE *source, *vm;
    CODE* c;

    for (int i = 0; i < size; i++)
    {
        set_filenames(path, input, output, compare, i);

        source = fopen(input, "r");
        vm = fopen(output, "w");

        c = new_code(source, NULL, vm);

        tested(c);

        release_code(c);

        result = get_file(output);
        expected = get_file(compare);

        if (strcmp(result, expected) != 0)
        {
            display_results(expected, result, i);
            return 0;
        }

        release_results(expected, result);

    }

    return 1;


}
