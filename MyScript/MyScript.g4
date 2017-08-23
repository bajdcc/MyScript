grammar MyScript;

start : exprs;

exprs : expr+;

expr : atom
     | list
	 | quote
     ;

quote : '\'' atom
      | '\'' list;

list : '(' ')'
     | '(' exprs ')'
     ;
atom : ID
     | NUM
	 | STRING
	 ;

WS : [ \t\r\n]+ -> skip ;
LINE_COMMENT : '//' .*? '\n' -> skip ;
COMMENT : '/*' .*? '*/' -> skip ;

ID : [a-zA-Z_!\-~%^&*?+/<>=]+ ;
STRING : '"' ('\\"'|.)*? '"' ;
NUM : [1-9][0-9]*|[0]|([0-9]+[.][0-9]+) ;