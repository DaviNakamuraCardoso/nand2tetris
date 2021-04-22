#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <table.h>
#include <parser.h>
#include <hasm.h>


int main(int argc, char* argv[])
{
    char* program, *name;
    int len;
    unsigned short symbolic;
    TABLE* root;
    FILE *src, *src_second, *src_third, *dest, *err;

    if (argc < 2) {
        printf("Source file not specified.\nUsage: ./hasm <filename>\n");
        return 1;
    }

    // Program name
    program = argv[1];
    len = strlen(program);
    name = (len > 7)? filename(program, len+1) : "out.hack";
    printf("Assembling %s\n", name);

    // Opening streams
    printf("Opening source files...\n");
    src = fopen(program, "r");
    src_second = fopen(program, "r");
    dest = fopen(name, "w");
    err = fopen("error.txt", "w");
    printf("Done opening files.\n");

    // Redirect the standard error to the text file
    dup2(fileno(err), 2);

    // Adding all commands
    printf("Setting up the commands...\n");
    root = setup();
    printf("Done setting up the commands.\n");

    // Adding all the labels
    setup_labels(root, src);

    // In the first pass, set up the variables and labels
    printf("Setting up variables...\n");
    setup_vars(root, src_second);
    printf("Done setting up variables.\n");

    // In the second pass, parse the file
    src_third = fopen("hack.out", "r");
    printf("Parsing...\n");
    parse(root, src_third, dest);
    printf("Done.\n");
    fclose(src_third);

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

        fclose(f);

    }

    return root;

}
