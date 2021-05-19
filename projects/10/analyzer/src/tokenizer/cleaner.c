/*** Cleaner */

#include <stdio.h>
#include <stdlib.h>
#include <tokenizer/tokens.h>
#include <tokenizer/reader.h>
#include <tokenizer/cleaner.h>


unsigned long long escape_string_literals(char* source, FILE* f)
{
    unsigned long long l = 0;

    if (source[l] == '"')
    {
        do {
            fputc(source[l], f);
        } while (source[++l] != '"');

        fputc('"', f);

    }


    return l;
}

unsigned long long split_implemented_symbols(char* source, unsigned long long l, FILE* f, SYMBOL* root)
{
    if (search_one_char(root, source+l))
    {
        if (source[l-1] != '\n') fputc('\n', f);
        fputc(source[l], f);
        if (!search_one_char(root, source+l+1) && source[l+1] != '\n') fputc('\n', f);
        return 1;
    }

    return 0;
}

char* split_symbols(char* source)
{
    // Very big number
    unsigned long long i, symbol, strings;
    FILE* f;
    SYMBOL* symbols;

    symbols = new_symbol();
    add_symbols_from_file(symbols, "../syntax/symbols.csv");

    f = fopen("tokens.out", "w");
    for (i = 0; source[i] != '\0'; i++)
    {
        // Parse string literals
        strings = escape_string_literals(source+i, f);
        if (strings > 0) { i += strings; continue; }

        // Parse symbols
        symbol = split_implemented_symbols(source, i, f, symbols);
        if (symbol) continue;

        // Parse common code
        fputc(source[i], f);
    }

    fclose(f);

    return get_file("tokens.out");
}
