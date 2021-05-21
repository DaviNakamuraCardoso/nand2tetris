/**
*      Parser module for the DCC Tokenizer
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer/tokens.h>
#include <tokenizer/reader.h>
#include <tokenizer/precomp.h>
#include <tokenizer/cleaner.h>
#include <tokenizer/parser.h>


void write_xml(char* tagname, char* content, FILE* xml)
{
    char opentag[100], closetag[100], final[500];

    sprintf(opentag, "<%s>", tagname);
    sprintf(closetag, "</%s>", tagname);
    sprintf(final, "%s%s%s", opentag, content, closetag);

    fprintf(xml, "%s", final);

    return;
}


char* get_token_content(TOKEN_TYPE t, char* token)
{
    char* content, *close;

    switch (t)
    {
        case STRING_LITERAL:
        {
            content = token+1;
            close = strchr(content, '"');
            *close = '\0';
            break;
        }
        default:
        {
            content = token;
            break;
        }
    }
    return content;
}


void get_tag(SYMBOL* root, char* token, FILE* f)
{
    char* content, *tag;
    TOKEN_TYPE t;

    t = get_type(root, token);
    content = get_token_content(t, token);
    tag = get_tagname(t);

    write_xml(tag, content, f);

    return;
}


unsigned int get_source_line(char* buff, char* source)
{
    unsigned int i = 0;

    if (*source == '\0') return 0;

    while ((*source) != '\n')
    {
        buff[i] = (*source);
        i++;
        source++;
    }
    buff[i] = '\0';

    return (++i);
}


char* get_xml(char* source)
{
    int size;
    char buff[10000], *tagname;
    SYMBOL* types_table = new_types_table();

    FILE* xml = fopen("tokens.xml", "w");

    while (*source != '\0')
    {
        size = get_source_line(buff, source);
        get_tag(types_table, buff, xml);
        source += size;
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


char* get_tagname(TOKEN_TYPE type)
{
    char* tag;

    switch (type) {

        case IMPLEMENTED_SYMBOL: {
            tag = "symbol"; break; }
        case KEYWORD: {
            tag = "keyword"; break; }
        case STRING_LITERAL: {
            tag = "stringConstant"; break; }
        case VARIABLE: {
            tag = "identifier"; break; }
        case NUMBER_CONSTANT: {
            tag = "integerConstant"; break; }
        default: {
            tag = "invalid"; break;
        }
    }

    return strdup(tag);
}


char* tokenize(char* filename)
{
    char* precompiled;

    precompiled = precompile(filename);

    return precompiled;
}
