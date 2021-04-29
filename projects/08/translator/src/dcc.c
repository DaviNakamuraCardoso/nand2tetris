/*
    Source code for the backend of Davi Compiler Collection (DCC)
    Translates Virtual Machine code (.vm) to Hack Assembly Language (.asm)
    Usage:
        $./dcc <filename.vm>
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree.h>
#include <functioncmds.h>
#include <commands.h>
#include <parser.h>
#include <writer.h>
#include <dcc.h>


int main(argc, argv)
int argc; char** argv;
{
    char *destination, *source;
    FILE *src, *dest;

    // Checks for usage errors
    if (argc != 2) {
        printf("No target provided.\nUsage: $./dcc <filename.vm>\n");
    }

    // Opens up the files
    source = argv[1];
    src = fopen(source, "r");
    if (src == NULL) error("Source file does not exist");

    // Get the destination filename
    destination = parse_filename(source);
    dest = fopen(destination, "w");


    // Basic initial commands

    fprintf(dest, "\n@256\nD=A\n@SP\nM=D\n@300\nD=A\n@LCL\nM=D\n@400\nD=A\n@ARG\nM=D\n@3000\nD=A\n@THIS\nM=D\n@3010\nD=A\n@THAT\nM=D\n");
    // Perform the translation
    base_translation(src, dest);


    // Close all files
    fclose(src);
    fclose(dest);

    // Free destination
    free(destination);

    return 0;
}

// Translates arithmetic operations and memory accesses from VM to Hack Assembly
void base_translation(FILE* f, FILE* d)
{
    int args;
    char **destination, *buff, comment[802], *cmd1, *cmd2, *cmd3, *translation;
    COMMAND p;
    TREE* root;

    root = init_tree();
    add_all_commands(root);
    destination = malloc(4*sizeof(char*));

    buff = malloc(800*sizeof(char));


    args = 0;
    while (fgets(buff, 800, f) != NULL)
    {
        fprintf(stderr, "Scanning %s...\n", buff);
        cmd1 = malloc(1000*sizeof(char));
        cmd2 = malloc(1000*sizeof(char));
        cmd3 = malloc(1000*sizeof(char));

        cmd1[0] = '\0';
        cmd2[0] = '\0';
        cmd3[0] = '\0';

        destination[0] = cmd1;
        destination[1] = cmd2;
        destination[2] = cmd3;

        args = parse_line(buff, destination);
        fprintf(stderr, "Line %s parsed\n", buff);

        translation = NULL;

        fprintf(stderr, "CMD1 is %s\n", cmd1);
        fprintf(stderr, "CMD2 is %s\n", cmd2);
        fprintf(stderr, "CMD3 is %s\n", cmd3);

        fprintf(stderr, "Args is now %i\n", args);

        if (args == 3) {

            fprintf(stderr, "About to parse a function command.\n");
            p = (cmd1[1] == 'u')? PUSH : POP;

            fprintf(stderr, "p is %i\n", p);

            if (*cmd1 == 'p')
            {
                translation = search_command(root, cmd2, atoi(cmd3), p);
            }
            else
            {
                translation = function_manager(cmd1, cmd2, cmd3);
            }

        } else if (args == 2) {
            fprintf(stderr, "About to print a branch command.\n");
            translation = branch_manager(cmd1, cmd2);
        } else if (args == 1){
            translation = arithmetic_manager(cmd1);
        }

        fprintf(d, "// %s\n", buff);

        fprintf(stderr, "%s\n", translation);

        if (translation != NULL) {
            write_line(translation, d);
            free(translation);
        }


        free(cmd1);
        free(cmd2);
        free(cmd3);
        free(buff);

        buff = malloc(800*sizeof(char));

    }

    // Safe EOF
    /*
    (END)
    @END
    0;JMP
    **/
    fprintf(d, "(END)\n@END\n0;JMP\n");
    return;


}

// Displays error message and exits the program
void error(message)
char* message;
{
    fprintf(stderr, "======== ERROR ==========\n%s\n", message);
    exit(1);
}
