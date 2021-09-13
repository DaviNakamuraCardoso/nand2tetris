#include <stdio.h>
#include <stdlib/stdio.h>
#include <stdlib/memory.h>
#include <stdlib/stdjl.h>
#include <tokenizer.h>


static Std library[] = {
    (Std) {.name="Memory.alloc", .f=std_malloc}, 
    (Std) {.name="Memory.deAlloc", .f=std_free}, 
    (Std) {.name="Output.putc", .f=std_putc}, 
    (Std) {.name="Output.printf", .f=std_printf},
    (Std) {.name="Keyboard.getString", .f=std_getstring},
    (Std) {.name="String.new", .f=std_string}, 
    (Std) {.name="String.appendChar", .f=std_appendchar}, 
    (Std) {.name="Array.new", .f=std_array} 
};


int stdlib(Source* s)
{
    for (int i = 0; i < sizeof(library) / sizeof(Std); i++)
    {
        add_map(s->indexes, library[i].name);
        s->labels[i+1] = library[i].f; 
    }
    s->stdcount = s->indexes->counter; 

    return 0;
}
