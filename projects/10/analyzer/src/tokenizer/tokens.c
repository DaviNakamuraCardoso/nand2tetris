/*** Define the data structures for the tokenizer **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer/tokens.h>
#include <utils/error.h>


SYMBOL* new_symbol(void)
{
    unsigned short s;
    SYMBOL* new;

    new = malloc(sizeof(SYMBOL));

    for (s = 0; s < MAX_ASCII; s++)
    {
        new->next[s] = NULL;
    }

    new->exists = 0;

    return new;
}


void release_symbol(SYMBOL** root)
{
    short s;

    if (root == NULL) return;
    if (*root == NULL) return;

    for (s = 0; s < MAX_ASCII; s++)
    {
        release_symbol(&(*root)->next[s]);
    }


    free(*root);
    *root = NULL;
    return;
}


void add_symbol(SYMBOL* root, char* key)
{
    short s, ascii;
    SYMBOL* current;

    if (root == NULL) return;

    current = root;
    for (s = 0; key[s] != '\0'; s++)
    {
        ascii = (int) key[s];
        if (current->next[ascii] == NULL)
        {
            current->next[ascii] = new_symbol();
        }
        current = current->next[ascii];
    }

    current->exists = 1;

    return;
}


unsigned int search_symbol(SYMBOL* root, char* key)
{
    short s, ascii;
    SYMBOL* current;

    current = root;
    for (s = 0; key[s] != '\0'; s++)
    {
        ascii = (int) key[s];
        if (current->next[ascii] == NULL) return 0;
        current = current->next[ascii];
    }

    if (current == NULL) return 0;

    return (current->exists);
}


unsigned int search_one_char(SYMBOL* root, char* key)
{
    char character[2];

    character[0] = key[0];
    character[1] = '\0';

    return search_symbol(root, character);
}


void add_symbols_from_file(SYMBOL* root, char* filename)
{
    char* buff, *whitespace = NULL;
    size_t size, len;
    FILE* f = fopen(filename, "r");

    if (f == NULL) error("Provided file does not exist.\n");

    len = 0;
    while ((size = getline(&buff, &len, f)) != -1)
    {
        // Remove the newline character
        buff[size-1] = '\0';

        // Remove whitespaces at the end of the string
        whitespace = strchr(buff, ' ');
        if (whitespace != NULL) *whitespace = '\0';

        add_symbol(root, buff);
    }

    fclose(f);

    return;
}
