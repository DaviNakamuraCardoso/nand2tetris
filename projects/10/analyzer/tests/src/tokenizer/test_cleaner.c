/** Test the cleaner module */


#include <stdio.h>
#include <stdlib.h>
#include <tokenizer/cleaner.h>

unsigned int test_split_spaces(void)
{
    char* result, *expected;

    expected = "class\nMain\n{\nfunction\nvoid\nmain\n(\n)\n{\n}\n}\n";
    result = split_symbols("class\nMain\n{\nfunction\nvoid\nmain()\n{\n}\n}\n");

    if (strcmp(result, expected) != 0)
    {
        printf("Result: %s\n", result);
        printf("Expected: %s\n", expected);

        free(result);
        return 0;
    }

    free(result);
    return 1;
}

unsigned int test_split_spaces_string_literals(void)
{

    unsigned short size, s;
    char* result;

    char* input[] = {
        "class\nMain\n{\nfunction\nvoid\nmain()\n{\ndo\nOutput.printString(\n\"Hello, World\"\n);\n}\n}\n"
    };

    char* expected[] = {
        "class\nMain\n{\nfunction\nvoid\nmain\n(\n)\n{\ndo\nOutput\n.\nprintString\n(\n\"Hello, World\"\n)\n;\n}\n}\n"
    };

    size = 1;

    for (s = 0; s < size; s++)
    {
        result = split_symbols(input[s]);

        if (strcmp(result, expected[s]) != 0)
        {
            printf("Result: %s\n", result);
            printf("Expected: %s\n", expected[s]);
            free(result);
            return 0;
        }

        free(result);
    }


    return 1;

}

unsigned int test_cleaner(void)
{
    unsigned short i, size;

    unsigned int (*tests[]) (void) = {
        test_split_spaces,
        test_split_spaces_string_literals
    };

    size = 2;
    for (i = 0; i < size; i++)
    {
        if (!tests[i]())
        {
            printf("Error in comparison %i\n", i);
            return 0;
        }
    }

    return 1;
}
