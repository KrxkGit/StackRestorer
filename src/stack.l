%{
#include "stack.tab.h"
%}


%%
pc[ \t][0-9a-fA-F]+  { /* 匹配堆栈地址 */ yylval.str = _strdup(yytext + 3); return ADDRESS; }
([^/|^!]+\.(?:so|dll))    { yylval.str = _strdup(yytext); return SONAME; }
\n                  { return NEWLINE; }
[ \t]+              ; // 忽略空白字符
.                   { /* 忽略其他字符 */ }

%%

// 额外的代码

int yywrap() {
    return 1;
}