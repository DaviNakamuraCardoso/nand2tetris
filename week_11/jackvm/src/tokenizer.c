#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ascii.h>
#include <tokenizer.h>
#include <tokens.h>
 
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

int tokenize(FILE* stream)
{
    char buff[300]; 

    sh** cmds = cmdhash();
    sh** msegs = mseghash(); 

    while (getword(stream, buff) != NULL) 
    {
        short type = gethash(cmds, buff);
        if (type == -1) type = gethash(msegs, buff);

        printf("%s", buff);
        printf(" %i\n", type);
    }

    return 0; 

}

