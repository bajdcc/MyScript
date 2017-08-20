grammar MyScript;

start : expr;

expr : expr op=('*'|'/') expr
     | expr op=('+'|'-') expr
     | value
     | '(' expr ')'
;

value : INT;

WS : [ \t\r\n]+ -> skip ; 

ID : [a-zA-Z]+ ;
INT : [0-9]+ ;