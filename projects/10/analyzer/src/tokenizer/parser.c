/**
*      Parser module for the DCC Tokenizer
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer/tokens.h>
#include <tokenizer/precomp.h>
#include <tokenizer/cleaner.h>

void release_result(char** result)
{
    if (result == NULL) return;

    if (result[1] != NULL) free(result[1]);
    if (result[2] != NULL) free(result[2]);

    free(result);
    return;
}



void write_xml(char* tagname, char* content, FILE* xml)
{
    char opentag[200], closetag[200], final[500];

    sprintf(opentag, "<%s>", tagname);
    sprintf(closetag, "</%s>", tagname);
    sprintf(final, "%s%s%s", opentag, content, closetag);

    fprintf(xml, "%s\n", final);

    return;
}

char* get_tagname(SYMBOL* root, char* token)
{
    TOKEN_TYPE t;
    t = get_token_type(root, token);
    return get_tag(t);
}

unsigned int get_source_line(char* buff, char* source)
{
    unsigned int i = 0;

    if (*source == '\0') return 0;

    while ((*source) != '\n')
    {
        buff[i++] = source++;
    }

    return 1;
}

char* get_xml(char* buff)
{
    SYMBOL* types_table = new_types_table();
    char buff[10000] = '\0';
    FILE* xml = fopen("tokens.xml");

    while (get_source_line(buff, source))
    {
        write_xml(get_tagname(types_table, buff), buff, xml);
    }

    fclose(xml);

    return get_file("tokens.xml");
}

SYMBOL* new_types_table(void)
{
    SYMBOL* root;

    root = new_symbol();

    add_symbols_from_file(root, "./syntax/keywords.csv", KEYWORD);
    add_symbols_from_file(root, "./syntax/symbols.csv", IMPLEMENTED_SYMBOL);

    return root;

}

TOKEN_TYPE get_type(SYMBOL* types_table, char* token)
{
    TOKEN_TYPE type;

    type = string_or_constant(token);

    if (type != -1) {
        return type;
    }

    type = get_token_type(types_table, token);

    if (type != -1) {
        return type;
    }

    type = check_variable(token);

    return type;
}


char* get_tag(TOKEN_TYPE type)
{
    char* tag;

    switch (type) {

        case IMPLEMENTED_SYMBOL: {
            tag = "symbol"; break; }
        case KEYWORD: {
            tag = "keyword"; break; }
        case STRING_LITERAL: {
            tag = "StringConstant"; break; }
        case VARIABLE: {
            tag = "variable"; break; }
        case NUMBER_CONSTANT: {
            tag = "numberConstant"; break; }
    }

    return strdup(tag);
}


char* tokenize(char* filename)
{
    char* precompiled;

    precompiled = precompile(filename);

    return precompiled;
}
