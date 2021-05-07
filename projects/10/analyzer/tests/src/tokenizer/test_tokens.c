/**
*       Test the tokenizer module
*/


#include <stdio.h>
#include <stdlib.h>
#include <tokenizer/tokens.h>


unsigned int test_if_new_symbol_is_not_null(void)
{
    unsigned int result;
    SYMBOL* root;

    root = create_symbol();
    result = (root != NULL);
    free(root);

    if (!result)
        printf("FAIL in creation of symbols: create_symbol returns NULL.\n");

    return (result);

}

unsigned int test_if_new_symbol_does_not_exist(void)
{
    unsigned int result;
    SYMBOL* s;
    s = create_symbol();
    result = (s->exists == 0);

    if (!result)
        printf("ERROR: New symbols are supposed to have the 'exists' field set to 0\n");

    free(s);
    return result;
}

unsigned int test_if_new_symbol_has_all_next_set_to_null(void)
{
    int i;
    unsigned int result;
    SYMBOL* s;

    s = create_symbol();
    for (i = 0; i < SYMBOL_NUM; i++)
    {
        if (s->next[i] != NULL)
        {
            printf("New symbols must have all next fields set to NULL.\n");
            return 0;
        }
    }

    free(s);

    return 1;
}

unsigned int successfully_release_root(void)
{
    unsigned int result;
    SYMBOL* root;
    root = create_symbol();
    release_symbol(&root);

    result = (root == NULL);

    if (!result)
        printf("Could not release root.\n");

    return (result);
}


unsigned int adding_strings_does_not_fail(void)
{
    SYMBOL* s;
    s = create_symbol();

    add_symbol(s, "&");
    add_symbol(s, "&a");

    if (!s->next['&']->exists || !(s->next['&']->next['a']->exists)) {
        printf("Fail adding values in tree\n");
        return 0;
    }

    release_symbol(&s);

    return 1;
}

// Adds elements to a trie and searches for them
unsigned int search_in_tree(void)
{
    int size, i;
    SYMBOL* root;


    char* symbols[] = {
        "this",
        "that",
        "&",
        "=",
        "if",
        "&&&"
    };

    char* doesnt_exist[] = {
        "my_var",
        "thi",
        "switch_in_python",
        "fast_python_programs",
        "&&",
        "this_"
    };

    size = 6;

    root = create_symbol();
    for (i = 0; i < size; i++)
    {
        add_symbol(root, symbols[i]);
    }


    for (i = 0; i < size; i++)
    {
        if (!search_symbol(root, symbols[i]))
        {
            printf("Could not save %s in tree.\n", symbols[i]);
            return 0;
        }
    }

    for (i = 0; i < size; i++)
    {
        if (search_symbol(root, doesnt_exist[i]))
        {
            printf("False response: %s wasn't added to tree.\n", doesnt_exist[i]);
            return 0;
        }
    }

    release_symbol(&root);

    return 1;
}


unsigned int test_tokenizer(void)
{
    int test_num, i;

    unsigned int (*tests[]) (void) = {
        test_if_new_symbol_is_not_null,
        test_if_new_symbol_does_not_exist,
        test_if_new_symbol_has_all_next_set_to_null,
        successfully_release_root,
        adding_strings_does_not_fail,
        search_in_tree
    };

    test_num = 6;

    for (i = 0; i < test_num; i++)
    {
        if (!tests[i]())
        {
            printf("Fail in tokenizer.\n");
            printf("Fail on test %i\n", i);
            return 0;
        }
    }

    return 1;

}
