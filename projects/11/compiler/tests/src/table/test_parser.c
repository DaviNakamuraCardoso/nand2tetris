/**
*
*       Test the parser module for tables
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <table/parser.h>
#include <utils/tests.h>

static unsigned int test_xmlnode(void)
{
    unsigned int status;
    XML* xml = NULL;

    xml = new_xml();
    status = xml != NULL;
    free(xml);

    return status;
}



unsigned int test_xmlparser(void)
{
    unsigned int (*tests[]) (void) = {
        test_xmlnode
    };

    return test(tests, 1);
}
