#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <table.h>
#include <parser.h>
#include <hasm.h>

int main(int argc, char* argv[])
{
    char* program, *name;
    int len;
    TABLE* root;
    FILE* src, *dest;


    if (argc < 2) {
        printf("Source file not specified.\nUsage: ./hasm <filename>\n");
        return 1;
    }

    // Program name
    program = argv[1];
    len = strlen(program);
    name = (len > 7)? filename(program, len+1) : "out.hack";

    printf("Assembling %s\n", name);

    src = fopen(program, "r");
    dest = fopen(name, "w");

    root = setup();

    add_symbols(root, src, dest);



    return 0;
}

TABLE* setup(void)
{
    TABLE* root;
    FILE* f;
    int i, size;

    root = init_table(NULL, 0);
    size = 4;
    char* command_list[4] = {
        "assembler/commands/comp.csv",
        "assembler/commands/dest.csv",
        "assembler/commands/jump.csv",
        "assembler/commands/macros.csv"
    };

    for (i = 0; i < size; i++) {
        // Opens command CSV
        f = fopen(command_list[i], "r");

        // add_values closes the file automatically
        add_values(root, f);

    }

    return root;

}
