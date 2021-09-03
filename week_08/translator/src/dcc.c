/*
    Source code for the backend of Davi Compiler Collection (DCC)
    Translates Virtual Machine code (.vm) to Hack Assembly Language (.asm)
    Usage:
        $./dcc <filename.vm>
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <tree.h>
#include <functioncmds.h>
#include <commands.h>
#include <parser.h>
#include <writer.h>
#include <dcc.h>


int main(argc, argv)
int argc; char** argv;
{
    char *destination, *source, *full_path;
    struct dirent* de;
    FILE *src, *dest;
    DIR *dir;

    // Checks for usage errors
    if (argc != 2) {
        printf("No target provided.\nUsage: $./dcc <filename.vm>\n");
    }

    // Opens up the files
    source = argv[1];

    if (is_dir(source))
    {
        fprintf(stderr, "Printing directory\n");
        dir = opendir(source);
        destination = parse_dirname(source);

        fprintf(stderr, "Dirname is %s\n", destination);

        if (dir == NULL) error("Could not open given directory");

        dest = fopen(destination, "w");

        // Initial definitions
        dir_defs(dest);
        bootcode(dest);

        fprintf(stderr, "About to loop.\n");

        while ((de = readdir(dir)) != NULL)
        {
            full_path = malloc(1000*sizeof(char));
            fprintf(stderr, "%s\n", de->d_name);
            if (is_vm(de->d_name))
            {
                sprintf(full_path, "%s/%s", source, de->d_name);
                src = fopen(full_path, "r");
                base_translation(src, dest, de->d_name);
                fclose(src);
            }
            free(full_path);
        }

        closedir(dir);
        fclose(dest);
        free(destination);

        return 0;
    }

    src = fopen(source, "r");
    if (src == NULL) error("Source file does not exist");

    // Get the destination filename
    destination = parse_filename(source);
    dest = fopen(destination, "w");


    // Perform the translation
    base_translation(src, dest, destination);


    // Close all files
    fclose(src);
    fclose(dest);

    // Free destination
    free(destination);

    return 0;
}

// Translates arithmetic operations and memory accesses from VM to Hack Assembly
void base_translation(FILE* f, FILE* d, char* filename)
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
                if (strstr(cmd2, "static") != NULL) {
                    translation = static_man(cmd1, atoi(cmd3), filename);
                } else {
                    translation = search_command(root, cmd2, atoi(cmd3), p);
                }
            }
            else
            {
                translation = function_manager(cmd1, cmd2, cmd3);
            }

        } else if (args == 2 && strlen(cmd2) > 1) {
            fprintf(stderr, "About to print a branch command.\n");
            translation = branch_manager(cmd1, cmd2);
        } else if (args == 1 || strlen(cmd2) <= 1){
            fprintf(stderr, "About to parse a 1 arg command\n");
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

    return;


}

// Checks if a name is a dir or not
unsigned int is_dir(const char* name)
{
    int i;
    for (i = 0; name[i] != '\0'; i++)
    {
        if (name[i] == '.') return 0;
    }

    return 1;
}

// Checks if a given file is a Virtual Machine file or not
unsigned int is_vm(const char* filename)
{
    return (strstr(filename, ".vm") != NULL);
}

// Displays error message and exits the program
void error(message)
char* message;
{
    fprintf(stderr, "======== ERROR ==========\n%s\n", message);
    exit(1);
}
