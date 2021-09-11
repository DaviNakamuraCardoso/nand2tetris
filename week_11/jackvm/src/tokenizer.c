#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ascii.h>
#include <tokenizer.h>
#include <tokens.h>
#include <list.h>
 
static char* getword(FILE* stream, char* buff)
{
fstart: {}

    int i = 0; 
    char c;

    buff[0] = '\0'; 

    if ((c = fgetc(stream)) == EOF) return NULL;

    if (isnullchar(c))
    {
        do {
            c = fgetc(stream);
            if (c == EOF) return NULL; 
        } while (isnullchar(c));
    }

    if (issym(c)) 
    {
        do {
            buff[i++] = c; 
        } while (isvalidsym((c = fgetc(stream)), buff, i));
        ungetc(c, stream); 

        goto end; 
    }

    do {
        buff[i++] = c;
    } while (iscmd((c = fgetc(stream))));

end: 
    buff[i] = '\0'; 

    if (iscommentstart(buff)) { skipc(stream, buff); goto fstart; }

    return buff; 
}

List* tokenize(FILE* stream)
{
    char buff[300]; 
    unsigned short labelcount = 1; 
    unsigned long *labels = calloc(sizeof(unsigned long), 4000);

    List* tokens = new_list();
    Hash** cmds = cmdhash();
    Hash** msegs = mseghash(); 
    Hash** index = new_hash(); 
//    Hash** functions = new_hash(); 
//
    inline void getconstant(char* word)
    {
        long l = atol(word);
        for (int i = 0; i < 4; i++)
        {
            unsigned short s = 0;
            s |= l >> ((3-i)*16);

            addl(tokens, s); 
        }
    }
    
    inline void getspecial(char* word) 
    {
        short last = lastel(tokens), labeli = -1;
        if (isnumeral(word) && last != CONSTANT)
        {
            addl(tokens, atoi(word));
            return;
        }
        switch (last)
        {
            case CONSTANT: 
            { 
                getconstant(word); return;
            }
            case GOTO:
            case IFGOTO:
            case FUNCTION: 
            case CALL: 
            case LABEL: 
            {
                labeli = gethash(index, word); 
                if (labeli == -1) 
                { 
                    labeli = labelcount++;
                    add_hash(index, word, labeli);
                }

                addl(tokens, labeli);

                if (last == FUNCTION || last == LABEL) 
                { 
                    labels[labeli] = listlength(tokens); 
                }

                return;
            }
        } 
    }

    inline void generatetoken(char* word) 
    {
        short token = gethash(cmds, word);
        if (token == -1) token = gethash(msegs, word);
        if (token == -1)
        {
            getspecial(word);
            return;
        }

        addl(tokens, (unsigned short) token);
        return;
    }

    while (getword(stream, buff) != NULL) 
    {
        generatetoken(buff);
    }

    release_hash(cmds);
    release_hash(msegs);

    printf("%lu is LOOP\n", labels[1]);
    printf("%lu is HELLO\n", labels[2]); 

    return tokens; 

}

