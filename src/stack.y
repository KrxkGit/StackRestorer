%{
#include "main.h"

extern int yylex(void);  // 声明 yylex 函数
void yyerror(const char *s);

%}

%token <str> ADDRESS NEWLINE SONAME

%union
{ 
     int iValue; /* integer value */ 
     char* str; /* symbol table index */
}

%%
lines:
    | lines line
    ;

line:
    NEWLINE core
    | core

core:
    ADDRESS SONAME { add_items($1, $2); free($1); free($2); }
%%

void yyerror(const char *s) {  // 定义 yyerror 函数
    fprintf(stderr, "Error: %s\n", s);
}

int run_stack_dumper() {
    yyparse();
    return 0;
}