
enum command { 
    PUSH, 
    POP,
    LABEL,
    GOTO,
    IFGOTO,
    CALL,
    FUNCTION,
    ADD,
    SUB,
    MULT,
    DIV,
    GT,
    LT,
    EQ
}; 

enum memseg {
    STATIC,
    ARGUMENT,
    LOCAL, 
    THIS,
    THAT,
    POINTER,
    TEMP
};
    
typedef struct _token {
    enum command cmd;
    union {
        enum memseg ms;
        unsigned long address;
    };
    long value;
} Token; 


enum command cmdtype(char* cmd);
enum memseg memsegtype(char* memseg);
