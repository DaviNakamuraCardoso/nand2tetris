/*
    Source code for the backend of Davi Compiler Collection (DCC)
    Translates Virtual Machine code (.vm) to Hack Assembly Language (.asm)
    Usage:
        $./dcc <filename.vm>
*/
#include <stdio.h>
#include <stdlib.h>
#include <dcc.h>
#include <parser.h>
#include <writer.h>


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

    // Close all files
    fclose(src);
    fclose(dest);

    // Free destination
    free(destination);

    return 0;
}

// Translates arithmetic operations and memory accesses from VM to Hack Assembly
void base_translation(filename)
char* filename;
{
    // Put your code here

}

// Displays error message and exits the program
void error(message)
char* message;
{
    fprintf(stderr, "======== ERROR ==========\n%s\n", message);
    exit(1);
}
