

void compile_expression(CODE *c);

unsigned int compile_keywordconstant(CODE* c);
unsigned int compile_unaryop(CODE* c);
unsigned int compile_op(CODE* c);
unsigned int compile_term(CODE* c);
unsigned int compile_expressionlist(CODE* c);
unsigned int compile_inbraces(CODE* c);
unsigned int compile_subroutinecall(CODE* c);
unsigned int compile_arrayaccess(CODE* c); 
