/**
*
*          Useful functions to test the symbol table
*
*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <compengine/compile.h>
#include <compengine/structure.h>
#include <utils/tests.h>

unsigned int test_symbols(char* name, __VARIABLE** variables[], int size, void (*tested) (CODE*))
{
    char filename[200], filename2[200], filename3[200];
    FILE* input, *output;
    int ident = 0;

    for (int i = 0; i < size; i++)
    {
        set_filenames(name, filename, filename2, filename3, i);
        input = fopen(filename, "r");
        output = fopen(filename2, "w");

        CODE c = {.source=input, .target=output, .identation=&ident, .table=new_table("Main")};
        tested(&c);

        for (int j = 0; variables[i][j] != NULL; j++)
        {
            __VARIABLE* found = search_table(c.table, variables[i][j]->name);


            if (found == NULL)
            {
                fprintf(stderr, "Variable wasn't added to table.\n");
                return 0;
            }

            if (found->type != variables[i][j]->type)
            {
                fprintf(stderr, "Wrong type.\n");
                return 0;
            }

            if (found->kind != variables[i][j]->kind)
            {
                fprintf(stderr, "Wrong variable kind\n");
                return 0;
            }

            release_variable(variables[i][j]);
        }

        if (c.table->next != NULL)
        {
            exit_scope(&c);
        }

        fclose(input);
        fclose(output);

        release_table(&c.table);

    }

    return 1;
}
