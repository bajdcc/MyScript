grammar MyScript;

start : '(' ')'
      | '(' exprs ')';

exprs : expr+;

expr : atom
     | list
     ;

list : '(' ')'
     | '(' exprs ')'
     ;
atom : ID
     | NUM
	 ;

WS : [ \t\r\n]+ -> skip ; 

ID : [a-zA-Z_!\-~%^&*?+/<>]+ ;
NUM : [0-9]+ ;