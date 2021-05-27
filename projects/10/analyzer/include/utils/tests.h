// Run a set of test functions
unsigned int test(unsigned int (*tests[]) (void), unsigned short s);


// Compare
unsigned int generic_compare(const char* expression, void (*tested) (CODE*), unsigned short size);

unsigned int test_compile_implemented(const char* name, unsigned int (*function) (CODE*, char*), int size); 
